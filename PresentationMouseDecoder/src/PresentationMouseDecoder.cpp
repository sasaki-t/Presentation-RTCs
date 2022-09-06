// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  PresentationMouseDecoder.cpp
 * @brief Create slide change and draw commands for presentation component based on input mouse data
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#include <iostream>
#include <cstdlib>
#include <opencv2/highgui/highgui.hpp>

#include "PresentationMouseDecoder.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const presentationmousedecoder_spec[] =
#else
static const char* presentationmousedecoder_spec[] =
#endif
  {
    "implementation_id", "PresentationMouseDecoder",
    "type_name",         "PresentationMouseDecoder",
    "description",       "Create slide change and draw commands for presentation component based on input mouse data",
    "version",           "1.1.0",
    "vendor",            "TakeshiSasaki",
    "category",          "Presentation",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.SlideChangeClick", "1",

    // Widget
    "conf.__widget__.SlideChangeClick", "radio",
    // Constraints
    "conf.__constraints__.SlideChangeClick", "(1,2)",

    "conf.__type__.SlideChangeClick", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PresentationMouseDecoder::PresentationMouseDecoder(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_MouseEventIn("MouseEvent", m_MouseEvent),
    m_SlideRelativeCommandOut("SlideRelativeCommand", m_SlideRelativeCommand),
    m_DrawPositionsOut("DrawPositions", m_DrawPositions)
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PresentationMouseDecoder::~PresentationMouseDecoder()
{
}



RTC::ReturnCode_t PresentationMouseDecoder::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("MouseEvent", m_MouseEventIn);
  
  // Set OutPort buffer
  addOutPort("SlideRelativeCommand", m_SlideRelativeCommandOut);
  addOutPort("DrawPositions", m_DrawPositionsOut);

  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("SlideChangeClick", m_SlideChangeClick, "1");
  // </rtc-template>

  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PresentationMouseDecoder::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t PresentationMouseDecoder::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationMouseDecoder::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t PresentationMouseDecoder::onActivated(RTC::UniqueId /*ec_id*/)
{
    x_old = -1;
    y_old = -1;

    click_type = 0;

    while (m_MouseEventIn.isNew()) {
        m_MouseEventIn.read();
    }

    return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationMouseDecoder::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * InPortのMouseEventから値を読み込み、プレゼンテーションコンポーネ
 * ントのスライドページ変更コマンドとペン描画位置に対応する数値をO
 * utPortのSlideRelativeCommandとDrawPositionsからそれぞれ出力する
 * 。
 */

RTC::ReturnCode_t PresentationMouseDecoder::onExecute(RTC::UniqueId /*ec_id*/)
{
    const int thresh_d = 5; //if displacement is less than this value, we consider it is single click
    bool change = false;

    if (m_MouseEventIn.isNew()) {
        m_MouseEventIn.read();
        //Check data length
        if (m_MouseEvent.data.length() != 4) {
            std::cerr << "Invalid data length: MouseEvent" << std::endl;
            return RTC::RTC_OK;
        }

        std::cerr << "ev:" << m_MouseEvent.data[0] << " x:" << m_MouseEvent.data[1] << " y:" << m_MouseEvent.data[2] << " flag:" << m_MouseEvent.data[3] << std::endl;

        //Create slide change commands if click or double click done 
        if (m_SlideChangeClick == 2) { //Double click detection case
            if (m_MouseEvent.data[0] == cv::EVENT_LBUTTONDBLCLK) {
                m_SlideRelativeCommand.data = 1;
                change = true;
            }
            else if (m_MouseEvent.data[0] == cv::EVENT_RBUTTONDBLCLK) {
                m_SlideRelativeCommand.data = -1;
                change = true;
            }
        }
        else if (m_SlideChangeClick == 1) { //Single click detection case
         //If already button down, get displacement (Manhattan distance between current and previous positions)
            if (click_type != 0) {
                click_d += std::abs(click_x - m_MouseEvent.data[1]) + std::abs(click_y - m_MouseEvent.data[2]);
                click_x = m_MouseEvent.data[1];
                click_y = m_MouseEvent.data[2];
            }

            //Button down or release check
            if ((m_MouseEvent.data[0] == cv::EVENT_LBUTTONDOWN) || ((m_MouseEvent.data[0] == cv::EVENT_RBUTTONDOWN))) { //Button down
                if (click_type != 0) { //if other key already pressed - both left and right keys are being pressed
                    click_type = 0; //reset click condition (does not consider left or right click anymore)
                }
                else { //button down correctly detected (button down and no other flag) - initialize click type and position
                    if (m_MouseEvent.data[0] == cv::EVENT_LBUTTONDOWN && ((m_MouseEvent.data[3] == cv::EVENT_FLAG_LBUTTON) || (m_MouseEvent.data[3] == 0))) { click_type = 1; } //set corresponding click type - left click
                    else if (m_MouseEvent.data[3] == cv::EVENT_FLAG_RBUTTON || m_MouseEvent.data[3] == 0) { click_type = -1; } // - right click
                    //if(m_MouseEvent.data[0]==CV_EVENT_LBUTTONDOWN){click_type = 1;} //set corresponding click type - left click
                    //else{click_type = -1;} // - right click
                    //if click type does not set correctily, following initialization is no meaning
                    click_x = m_MouseEvent.data[1];
                    click_y = m_MouseEvent.data[2];
                    click_d = 0;
                }
            }
            else if (((click_type == 1) && ((m_MouseEvent.data[0] == cv::EVENT_LBUTTONUP) || ((m_MouseEvent.data[3] & cv::EVENT_FLAG_LBUTTON) == 0))) || ((click_type == -1) && ((m_MouseEvent.data[0] == cv::EVENT_RBUTTONUP) || ((m_MouseEvent.data[3] & cv::EVENT_FLAG_RBUTTON) == 0)))) { //if button released
                std::cout << click_d << '/' << thresh_d << std::endl;
                if (click_d < thresh_d) { // if mouse position does not change so much
                    m_SlideRelativeCommand.data = click_type; //change slide
                    change = true;
                }
                click_type = 0; //reset click condition
            }
        }

        //Output slide change command if necessary
        if (change) {
            setTimestamp(m_SlideRelativeCommand);
            m_SlideRelativeCommandOut.write();

            //clear draw position since slide page is changed
            x_old = -1;
            y_old = -1;

            return RTC::RTC_OK; //no need to create draw command when slide page is changed
        }

        //Create draw commands if dragged
        if (m_MouseEvent.data[3] != cv::EVENT_FLAG_LBUTTON) { //button released - clear old position
            x_old = -1;
            y_old = -1;
        }
        else {
            if (x_old < 0) { //we do not have old point - output current point
                m_DrawPositions.data.length(2);
                m_DrawPositions.data[0] = m_MouseEvent.data[1];
                m_DrawPositions.data[1] = m_MouseEvent.data[2];
            }
            else { //we have old point - output both previous and current points
                m_DrawPositions.data.length(4);
                m_DrawPositions.data[0] = x_old;
                m_DrawPositions.data[1] = y_old;
                m_DrawPositions.data[2] = m_MouseEvent.data[1];
                m_DrawPositions.data[3] = m_MouseEvent.data[2];
            }
            setTimestamp(m_DrawPositions);
            m_DrawPositionsOut.write();

            //store current position as old data for next step
            x_old = m_MouseEvent.data[1];
            y_old = m_MouseEvent.data[2];
        }

    }//endif(m_MouseEventIn.isNew())

    return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationMouseDecoder::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationMouseDecoder::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationMouseDecoder::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationMouseDecoder::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationMouseDecoder::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}



extern "C"
{
 
  void PresentationMouseDecoderInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentationmousedecoder_spec);
    manager->registerFactory(profile,
                             RTC::Create<PresentationMouseDecoder>,
                             RTC::Delete<PresentationMouseDecoder>);
  }
  
}
