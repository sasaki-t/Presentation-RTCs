// -*- C++ -*-
/*!
 * @file  CVPresentation.cpp
 * @brief Presentation component using OpenCV
 * @date $Date$
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#include <iostream>
#include <string>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "VectorConvert.h"

#include "CVPresentation.h"

//Mouse callback
bool mouse_update = false;
int mevent[4];
void onMouse(int event, int x, int y, int params, void* param){
  mouse_update = true;
  mevent[0] = event;
  mevent[1] = x;
  mevent[2] = y;
  mevent[3] = params;
  //std::cerr << "ev:" << event << " x:" << x << " y:" << y << " flag:" << params << std::endl;
};

// Module specification
// <rtc-template block="module_spec">
static const char* cvpresentation_spec[] =
  {
    "implementation_id", "CVPresentation",
    "type_name",         "CVPresentation",
    "description",       "Presentation component using OpenCV",
    "version",           "1.0.0",
    "vendor",            "TakeshiSasaki",
    "category",          "Presentation",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.SlideFilePath", "./",
    "conf.default.SlideFileName", "test***.jpg",
    "conf.default.SlideFileInitialNumber", "1",
    "conf.default.SlideNumberInRelative", "1",
    "conf.default.SlideSizeWidth", "0",
    "conf.default.SlideSizeHeight", "0",
    "conf.default.CommentColorRGB", "0,0,0",
    "conf.default.CommentSize", "1.0",
    "conf.default.CommentBaseSpeed", "4",
    "conf.default.PenColorRGB", "255,0,0",
    "conf.default.PenThickness", "4",
    // Widget
    "conf.__widget__.SlideFilePath", "text",
    "conf.__widget__.SlideFileName", "text",
    "conf.__widget__.SlideFileInitialNumber", "text",
    "conf.__widget__.SlideNumberInRelative", "radio",
    "conf.__widget__.SlideSizeWidth", "text",
    "conf.__widget__.SlideSizeHeight", "text",
    "conf.__widget__.CommentColorRGB", "text",
    "conf.__widget__.CommentSize", "text",
    "conf.__widget__.CommentBaseSpeed", "text",
    "conf.__widget__.PenColorRGB", "text",
    "conf.__widget__.PenThickness", "text",
    // Constraints
    "conf.__constraints__.SlideFileInitialNumber", "x>=0",
    "conf.__constraints__.SlideNumberInRelative", "(0,1)",
    "conf.__constraints__.SlideSizeWidth", "x>=0",
    "conf.__constraints__.SlideSizeHeight", "x>=0",
    "conf.__constraints__.CommentSize", "x>0",
    "conf.__constraints__.CommentBaseSpeed", "x>0",
    "conf.__constraints__.PenThickness", "x>0",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CVPresentation::CVPresentation(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_SlideNumberInIn("SlideNumberIn", m_SlideNumberIn),
    m_PenIn("Pen", m_Pen),
    m_CommentIn("Comment", m_Comment),
    m_SlideNumberOutOut("SlideNumberOut", m_SlideNumberOut),
    m_KeyOut("Key", m_Key),
    m_MouseEventOut("MouseEvent", m_MouseEvent),
    m_SlideSizeInfoPortPort("SlideSizeInfoPort")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CVPresentation::~CVPresentation()
{
}



RTC::ReturnCode_t CVPresentation::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("SlideNumberIn", m_SlideNumberInIn);
  addInPort("Pen", m_PenIn);
  addInPort("Comment", m_CommentIn);
  
  // Set OutPort buffer
  addOutPort("SlideNumberOut", m_SlideNumberOutOut);
  addOutPort("Key", m_KeyOut);
  addOutPort("MouseEvent", m_MouseEventOut);
  
  // Set service provider to Ports
  m_SlideSizeInfoPortPort.registerProvider("SlideSizeInfo", "Slide::SlideSizeInfo", m_SlideSizeInfo);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_SlideSizeInfoPortPort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("SlideFilePath", m_SlideFilePath, "./");
  bindParameter("SlideFileName", m_SlideFileName, "test***.jpg");
  bindParameter("SlideFileInitialNumber", m_SlideFileInitialNumber, "1");
  bindParameter("SlideNumberInRelative", m_SlideNumberInRelative, "1");
  bindParameter("SlideSizeWidth", m_SlideSizeWidth, "0");
  bindParameter("SlideSizeHeight", m_SlideSizeHeight, "0");
  bindParameter("CommentColorRGB", m_CommentColorRGB, "0,0,0");
  bindParameter("CommentSize", m_CommentSize, "1.0");
  bindParameter("CommentBaseSpeed", m_CommentBaseSpeed, "4");
  bindParameter("PenColorRGB", m_PenColorRGB, "255,0,0");
  bindParameter("PenThickness", m_PenThickness, "4");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CVPresentation::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CVPresentation::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CVPresentation::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t CVPresentation::onActivated(RTC::UniqueId ec_id)
{
  int res;
  std::string name = m_SlideFilePath;
  if((name.empty())||((name[name.size()-1] != '/')&&(name[name.size()-1] != '\\'))){
    name.push_back('/');
  }
  name += m_SlideFileName;

  res = slds.initialize(name.c_str(), m_SlideFileInitialNumber, cv::Size(m_SlideSizeWidth,m_SlideSizeHeight));
  if(res!=0){
    return RTC::RTC_ERROR;
  }

  res = cmtMgr.initialize(&(display_img), m_CommentBaseSpeed);
  if(res!=0){
    return RTC::RTC_ERROR;
  }

  //Create window and show initial slide
  window_name = m_SlideFileName.substr(0,m_SlideFileName.find("*"));
  cv::namedWindow(window_name, CV_WINDOW_AUTOSIZE);

  display_img = slds.slide_img;
  cv::imshow(window_name, display_img);

  //Set mouse callback
  cv::setMouseCallback(window_name, onMouse);
  m_MouseEvent.data.length(4);

  //Initialize for service port interface
  m_SlideSizeInfo.slide_width = slds.slide_img.cols;
  m_SlideSizeInfo.slide_height = slds.slide_img.rows;

  //Initialize InPort data
  if(m_SlideNumberInIn.isNew()){
    m_SlideNumberInIn.read();
  }
  if(m_PenIn.isNew()){
    m_PenIn.read();
  }
  if(m_CommentIn.isNew()){
    m_CommentIn.read();
  }

  return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t CVPresentation::onDeactivated(RTC::UniqueId ec_id)
{
  cv::destroyAllWindows();
  return RTC::RTC_OK;
}

/*!
 * InPortのSlideNumberInに入力された値に応じてスライドのページを変
 * 更する。また、その際には新たなスライド番号をOutPortのSlideNumbe
 * rOutから出力する。
 * InPortのPenに入力された座標に線を引く。
 * InPortのCommentに入力された文字列を表示する。
 * スライド上で操作したマウスイベントとキーボード入力をOutPortから
 * 出力する。
 */

RTC::ReturnCode_t CVPresentation::onExecute(RTC::UniqueId ec_id)
{
  unsigned int i;
  unsigned int data_length;
  int res;
  bool update_slide = false;

  //New slide number comes -- change slide image
  if(m_SlideNumberInIn.isNew()){
    m_SlideNumberInIn.read();
    res = slds.setSize(cv::Size(m_SlideSizeWidth, m_SlideSizeHeight));
    if(res==0){
      if(m_SlideNumberInRelative==1){
        res = slds.setRelative(m_SlideNumberIn.data);
      }else{
        res = slds.setAbsolute(m_SlideNumberIn.data);
      }

      if(res >= 0){ //if successfully changed, output new slide number
        update_slide = true;
        m_SlideNumberOut.data = slds.getSlideNumber();
        setTimestamp(m_SlideNumberOut);
        m_SlideNumberOutOut.write();

        //Update for service port interface
        m_SlideSizeInfo.slide_width = slds.slide_img.cols;
        m_SlideSizeInfo.slide_height = slds.slide_img.rows;
      }
    }
  }

  //New points come -- draw point or lines on slide image
  if(m_PenIn.isNew()){
    m_PenIn.read();
    if(m_Pen.data.length()%2!=0 || m_Pen.data.length()==0){
      std::cerr << "Invalid data length: Pen" << std::endl;
    }else{
      while(m_PenColorRGB.size()<3){
        m_PenColorRGB.push_back(0);
      }
      data_length = m_Pen.data.length()/2-1;
      if(data_length == 0){
        //cv::circle(slides.slide_img, cv::Point(m_Pen.data[0],m_Pen.data[1]), m_PenThickness, cv::Scalar(m_PenColorR, m_PenColorG, m_PenColorB), -1, CV_AA, 0);
        cv::line(slds.slide_img, cv::Point(m_Pen.data[0],m_Pen.data[1]), cv::Point(m_Pen.data[0],m_Pen.data[1]), cv::Scalar(m_PenColorRGB[2], m_PenColorRGB[1], m_PenColorRGB[0]), m_PenThickness, CV_AA, 0);
      }else{
        for(i=0;i<data_length;i+=2){
          cv::line(slds.slide_img, cv::Point(m_Pen.data[i],m_Pen.data[i+1]), cv::Point(m_Pen.data[i+2],m_Pen.data[i+3]), cv::Scalar(m_PenColorRGB[2], m_PenColorRGB[1], m_PenColorRGB[0]), m_PenThickness, CV_AA, 0);
        }
      }
      update_slide = true;
    }
  }

  //New comment comes -- store text
  if(m_CommentIn.isNew()){
    m_CommentIn.read();
    std::string st;
    st = m_Comment.data;
    if(!st.empty()){
      while(m_CommentColorRGB.size()<3){
        m_CommentColorRGB.push_back(0);
      }
      Comment cmt(Comment(st, cv::FONT_HERSHEY_COMPLEX, m_CommentSize, cv::Scalar(m_CommentColorRGB[2], m_CommentColorRGB[1], m_CommentColorRGB[0])));
      cmtMgr.addComment(cmt);
    }
  }

  //Update image
  if(update_slide || !cmtMgr.empty()){ //update if (slide changed or draw something) or (comments exist in previous stem)
    display_img = slds.slide_img.clone(); //slide + pen only -- since comments are moved from right to left, we need to reload the image without comments to erase comments in previous positions
    //Update comment -- put text
    res = cmtMgr.setSpeed(m_CommentBaseSpeed);
    if(res!=0){
      return RTC::RTC_ERROR;
    }

    res = cmtMgr.updateComment();
    //Show slide
    cv::imshow(window_name, display_img);
    //std::cout << display_img.cols << ' ' << display_img.rows << std::endl;
  }

  //key input -- output key
  res = cv::waitKey(30);
  if(res != -1){
    res &= 0xff;
    m_Key.data = (char)res;
    setTimestamp(m_Key);
    m_KeyOut.write();
  }

  //mouse update -- output mouse event
  if(mouse_update){
    mouse_update = false;
    for(i=0;i<4;i++){
      m_MouseEvent.data[i] = mevent[i];
    }
    setTimestamp(m_MouseEvent);
    m_MouseEventOut.write();
  }

  return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t CVPresentation::onAborting(RTC::UniqueId ec_id)
{
  cv::destroyAllWindows();
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CVPresentation::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CVPresentation::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CVPresentation::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CVPresentation::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CVPresentationInit(RTC::Manager* manager)
  {
    coil::Properties profile(cvpresentation_spec);
    manager->registerFactory(profile,
                             RTC::Create<CVPresentation>,
                             RTC::Delete<CVPresentation>);
  }
  
};


