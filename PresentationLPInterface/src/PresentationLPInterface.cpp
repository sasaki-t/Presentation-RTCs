// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  PresentationLPInterface.cpp
 * @brief Create slide change and draw commands for presentation component based on laser light pointing
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#include <iostream>
#include <cstring> //needed for memcpy()
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "PresentationLPInterface.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const presentationlpinterface_spec[] =
#else
static const char* presentationlpinterface_spec[] =
#endif
  {
    "implementation_id", "PresentationLPInterface",
    "type_name",         "PresentationLPInterface",
    "description",       "Create slide change and draw commands for presentation component based on laser light pointing",
    "version",           "1.0.0",
    "vendor",            "TakeshiSasaki",
    "category",          "Presentation",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.DetectLuminanceDiff", "30",
    "conf.default.DetectBgUpdate", "5",
    "conf.default.DetectUpdateTime", "0.5",
    "conf.default.ScreenZ", "0.0",
    "conf.default.SlideChangeArea", "top",
    "conf.default.SlideChangeAreaSize", "50",
    "conf.default.SlideChangeCount", "5",
    "conf.default.SlideChangeWait", "1.0",

    // Widget
    "conf.__widget__.DetectLuminanceDiff", "text",
    "conf.__widget__.DetectBgUpdate", "text",
    "conf.__widget__.DetectUpdateTime", "text",
    "conf.__widget__.ScreenZ", "text",
    "conf.__widget__.SlideChangeArea", "radio",
    "conf.__widget__.SlideChangeAreaSize", "text",
    "conf.__widget__.SlideChangeCount", "text",
    "conf.__widget__.SlideChangeWait", "text",
    // Constraints
    "conf.__constraints__.DetectUpdateTime", "x>=0",
    "conf.__constraints__.SlideChangeArea", "(top,left,right,bottom)",
    "conf.__constraints__.SlideChangeAreaSize", "x>0",
    "conf.__constraints__.SlideChangeCount", "x>0",
    "conf.__constraints__.SlideChangeWait", "x>=0",

    "conf.__type__.DetectLuminanceDiff", "int",
    "conf.__type__.DetectBgUpdate", "int",
    "conf.__type__.DetectUpdateTime", "double",
    "conf.__type__.ScreenZ", "double",
    "conf.__type__.SlideChangeArea", "string",
    "conf.__type__.SlideChangeAreaSize", "int",
    "conf.__type__.SlideChangeCount", "int",
    "conf.__type__.SlideChangeWait", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PresentationLPInterface::PresentationLPInterface(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_ImageIn("Image", m_Image),
    m_BgUpdateTriggerIn("BgUpdateTrigger", m_BgUpdateTrigger),
    m_SlideRelativeCommandOut("SlideRelativeCommand", m_SlideRelativeCommand),
    m_DrawPositionsOut("DrawPositions", m_DrawPositions),
    m_SlideSizeInfoPortPort("SlideSizeInfoPort")
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PresentationLPInterface::~PresentationLPInterface()
{
}



RTC::ReturnCode_t PresentationLPInterface::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Image", m_ImageIn);
  addInPort("BgUpdateTrigger", m_BgUpdateTriggerIn);
  
  // Set OutPort buffer
  addOutPort("SlideRelativeCommand", m_SlideRelativeCommandOut);
  addOutPort("DrawPositions", m_DrawPositionsOut);

  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_SlideSizeInfoPortPort.registerConsumer("SlideSizeInfo", "Slide::SlideSizeInfo", m_SlideSizeInfo);
  
  // Set CORBA Service Ports
  addPort(m_SlideSizeInfoPortPort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("DetectLuminanceDiff", m_DetectLuminanceDiff, "30");
  bindParameter("DetectBgUpdate", m_DetectBgUpdate, "5");
  bindParameter("DetectUpdateTime", m_DetectUpdateTime, "0.5");
  bindParameter("ScreenZ", m_ScreenZ, "0.0");
  bindParameter("SlideChangeArea", m_SlideChangeArea, "top");
  bindParameter("SlideChangeAreaSize", m_SlideChangeAreaSize, "50");
  bindParameter("SlideChangeCount", m_SlideChangeCount, "5");
  bindParameter("SlideChangeWait", m_SlideChangeWait, "1.0");
  // </rtc-template>

  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PresentationLPInterface::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t PresentationLPInterface::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationLPInterface::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t PresentationLPInterface::onActivated(RTC::UniqueId /*ec_id*/)
{
    bg_update = true;
    ptSc_old.x = -1;
    ptSc_old.y = -1;
    time_old.sec = 0;
    time_old.nsec = 0;
    area_index = -1;
    area_count = 0;

    while (m_ImageIn.isNew()) {
        m_ImageIn.read();
    }
    while (m_BgUpdateTriggerIn.isNew()) {
        m_BgUpdateTriggerIn.read();
    }

    return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationLPInterface::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * InPortのImageから読み込んだ画像から、スライド上のレーザポインタ
 * で指された位置を認識し、その位置に応じてプレゼンテーションコンポ
 * ーネントのスライドページ変更コマンドとペン描画位置に対応する数値
 * をOutPortのSlideRelativeCommandとDrawPositionsからそれぞれ出力す
 * る。
 */

RTC::ReturnCode_t PresentationLPInterface::onExecute(RTC::UniqueId /*ec_id*/)
{
    int i, j, res;
    int channels;
    cv::Mat image;
    cv::Point ptImg; //laser point position in the image coordinates
    cv::Point ptSc; //laser point position in the screen coordinates
    double intrinsic[3][3]; //camera intrinsic parameter 
    double extrinsic[3][4]; //camera extrinsic parameter

    bool continuous;
    bool is_change_area = false;
    cv::Rect change_area[3];
    int slide_width, slide_height;

    //Set background update flag if new update trigger comes
    if (m_BgUpdateTriggerIn.isNew()) {
        m_BgUpdateTriggerIn.read();
        bg_update = true;
    }

    //New image data
    if (m_ImageIn.isNew()) {
        m_ImageIn.read();

        //--- Convert ImageData to cv::Mat ---
        if (m_Image.data.image.format == Img::CF_RGB) {
            channels = 3;
            image.create(m_Image.data.image.height, m_Image.data.image.width, CV_8UC3);
        }
        else if (m_Image.data.image.format == Img::CF_GRAY) {
            channels = 1;
            image.create(m_Image.data.image.height, m_Image.data.image.width, CV_8UC1);
        }
        else {
            std::cerr << "Invalid data: Image" << std::endl;
            return RTC::RTC_OK;
        }

        for (i = 0; i < m_Image.data.image.height; ++i) {
            std::memcpy(&image.data[i * image.step], &m_Image.data.image.raw_data[i * m_Image.data.image.width * channels], sizeof(unsigned char) * m_Image.data.image.width * channels);
        }
        if (channels == 3) {
            cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        }
        // --- End convert ImageData to cv::Mat ---

        // --- Initialize backgournd image if necessary
        if (bg_update || lpd.backgroundEmpty()) {
            lpd.setBackgroundImage(image);
            bg_update = false;
            return RTC::RTC_OK;
        }
        // --- End initialize backgournd image if necessary ---

        // --- Main processing ---
        // *** set parameters
        lpd.setThreshold(m_DetectLuminanceDiff, m_DetectBgUpdate);
        // *** end set parameters

        //detection
        // *** read reconstruction parameters
        //read intrinsic parameters
        intrinsic[0][0] = m_Image.data.intrinsic.matrix_element[0];
        intrinsic[0][1] = m_Image.data.intrinsic.matrix_element[1];
        intrinsic[0][2] = m_Image.data.intrinsic.matrix_element[3];
        intrinsic[1][0] = 0;
        intrinsic[1][1] = m_Image.data.intrinsic.matrix_element[2];
        intrinsic[1][2] = m_Image.data.intrinsic.matrix_element[4];
        intrinsic[2][0] = 0;
        intrinsic[2][1] = 0;
        intrinsic[2][2] = 1;

        //read extrinsic parameters
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 4; j++) {
                extrinsic[i][j] = m_Image.data.extrinsic[i][j];
            }
        }
        // *** end read reconstruction parameters
        //get slide width and height
        try {
            slide_width = m_SlideSizeInfo->getWidth();
            slide_height = m_SlideSizeInfo->getHeight();
        }
        catch (CORBA::SystemException& e) {
            std::cerr << "ServicePort not connected." << std::endl;
            return RTC::RTC_ERROR;
        }
        if (slide_width <= 0 || slide_height <= 0) {
            std::cerr << "Invalid data form ServicePort: width=" << slide_width << ", height=" << slide_height << std::endl;
            return RTC::RTC_OK;
        }

        //res = lpd.detect(image, ptImg);
        res = lpd.detect(image, ptSc, cv::Point(0, 0), cv::Point(slide_width, slide_height), m_ScreenZ, intrinsic, extrinsic);
        if (res == 1) { //detected
          //coordinate transformation
          //ptSc = lpd.img_to_worldZ(ptImg, m_ScreenZ, intrinsic, extrinsic);
          //std::cout << "Im:" <<  ptImg.x << ',' << ptImg.y << "-> Sc:" << ptSc.x << ',' << ptSc.y << std::endl;
            std::cout << "-> Sc:" << ptSc.x << ',' << ptSc.y << std::endl;

            // *** generate commands for presentation component
            //check detected time
            setTimestamp(m_DrawPositions); //get current time
            if ((m_DrawPositions.tm.nsec - time_old.nsec) / 1.0e9 + (m_DrawPositions.tm.sec - time_old.sec) < m_DetectUpdateTime) {
                continuous = true;
            }
            else {
                continuous = false;
            }

            //set slide change region based on the slide width and height
            if (m_SlideChangeArea == "top" || m_SlideChangeArea == "bottom") {
                for (i = 0; i < 3; i++) {
                    change_area[i].x = slide_width * i / 3;
                    change_area[i].y = 0;
                    change_area[i].width = slide_width / 3;
                    change_area[i].height = m_SlideChangeAreaSize;
                }
                if (m_SlideChangeArea == "bottom") {
                    for (i = 0; i < 3; i++) {
                        change_area[i].y = slide_height - m_SlideChangeAreaSize; //bottom
                    }
                }
            }
            else if (m_SlideChangeArea == "left" || m_SlideChangeArea == "right") {
                for (i = 0; i < 3; i++) {
                    change_area[i].x = 0; //left
                    change_area[i].y = slide_height * i / 3;
                    change_area[i].width = m_SlideChangeAreaSize;
                    change_area[i].height = slide_height / 3;
                }
                if (m_SlideChangeArea == "right") {
                    for (i = 0; i < 3; i++) {
                        change_area[i].x = slide_width - m_SlideChangeAreaSize; //right
                    }
                }
            }

            //chack if the detected point is on the region
            for (i = 0; i < 3; i++) {
                if (change_area[i].contains(ptSc)) {
                    is_change_area = true;
                    if ((area_index == i) && (continuous)) {
                        area_count++;
                    }
                    else {
                        area_count = 1;
                        area_index = i;
                    }
                    if (area_count >= m_SlideChangeCount) {
                        //output slide change command
                        m_SlideRelativeCommand.data = area_index - 1;
                        setTimestamp(m_SlideRelativeCommand);
                        m_SlideRelativeCommandOut.write();

                        //reset counter and position
                        ptSc_old.x = -1;
                        ptSc_old.y = -1;
                        time_old.sec = 0;
                        time_old.nsec = 0;
                        area_index = -1;
                        area_count = 0;
                        cv::waitKey(m_SlideChangeWait * 1000);
                        return RTC::RTC_OK; //no need to send draw positions since the slide will be changed
                    }
                    break;
                }
            }
            if (!is_change_area) { //if not detected in slide change area  - reset counter
                area_index = -1;
                area_count = 0;
            }
            // *** end generate commands for presentation component

            // *** output
            //output drawing positions
            if (!continuous || ptSc_old.x < 0) { //we do not have old point - output current point
                m_DrawPositions.data.length(2);
                m_DrawPositions.data[0] = ptSc.x;
                m_DrawPositions.data[1] = ptSc.y;
            }
            else { //we have old point - output both previous and current points
                m_DrawPositions.data.length(4);
                m_DrawPositions.data[0] = ptSc_old.x;
                m_DrawPositions.data[1] = ptSc_old.y;
                m_DrawPositions.data[2] = ptSc.x;
                m_DrawPositions.data[3] = ptSc.y;
            }
            setTimestamp(m_DrawPositions);
            m_DrawPositionsOut.write();
            // *** end output

            //store current position as old data for next step
            time_old = m_DrawPositions.tm;
            ptSc_old = ptSc;

        }//end if(res==1)
        // --- End main processing ---
    } //end if(m_ImageIn.isNew())

    lpd.setBackgroundImage(image);
    cv::waitKey(30);

    return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationLPInterface::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationLPInterface::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationLPInterface::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationLPInterface::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationLPInterface::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}



extern "C"
{
 
  void PresentationLPInterfaceInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentationlpinterface_spec);
    manager->registerFactory(profile,
                             RTC::Create<PresentationLPInterface>,
                             RTC::Delete<PresentationLPInterface>);
  }
  
}
