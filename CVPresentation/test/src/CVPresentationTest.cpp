// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  CVPresentationTest.cpp
 * @brief Presentation component using OpenCV (test code)
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#include "CVPresentationTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const cvpresentation_spec[] =
#else
static const char* cvpresentation_spec[] =
#endif
  {
    "implementation_id", "CVPresentationTest",
    "type_name",         "CVPresentationTest",
    "description",       "Presentation component using OpenCV",
    "version",           "1.2.0",
    "vendor",            "TakeshiSasaki",
    "category",          "Presentation",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.SlideFilePath", "../../../tutorial",
    "conf.default.SlideFileName", "tutorial***.png",
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

    "conf.__type__.SlideFilePath", "string",
    "conf.__type__.SlideFileName", "string",
    "conf.__type__.SlideFileInitialNumber", "int",
    "conf.__type__.SlideNumberInRelative", "int",
    "conf.__type__.SlideSizeWidth", "int",
    "conf.__type__.SlideSizeHeight", "int",
    "conf.__type__.CommentColorRGB", "std::vector<int>",
    "conf.__type__.CommentSize", "double",
    "conf.__type__.CommentBaseSpeed", "int",
    "conf.__type__.PenColorRGB", "std::vector<int>",
    "conf.__type__.PenThickness", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CVPresentationTest::CVPresentationTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_SlideNumberInOut("SlideNumberIn", m_SlideNumberIn),
    m_PenOut("Pen", m_Pen),
    m_CommentOut("Comment", m_Comment),
    m_SlideNumberOutIn("SlideNumberOut", m_SlideNumberOut),
    m_KeyIn("Key", m_Key),
    m_MouseEventIn("MouseEvent", m_MouseEvent),
    m_SlideSizeInfoPortPort("SlideSizeInfoPort")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CVPresentationTest::~CVPresentationTest()
{
}



RTC::ReturnCode_t CVPresentationTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("SlideNumberOut", m_SlideNumberOutIn);
  addInPort("Key", m_KeyIn);
  addInPort("MouseEvent", m_MouseEventIn);
  
  // Set OutPort buffer
  addOutPort("SlideNumberIn", m_SlideNumberInOut);
  addOutPort("Pen", m_PenOut);
  addOutPort("Comment", m_CommentOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_SlideSizeInfoPortPort.registerConsumer("SlideSizeInfo", "Slide::SlideSizeInfo", m_SlideSizeInfo);
  
  // Set CORBA Service Ports
  addPort(m_SlideSizeInfoPortPort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("SlideFilePath", m_SlideFilePath, "../../../tutorial");
  bindParameter("SlideFileName", m_SlideFileName, "tutorial***.png");
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
RTC::ReturnCode_t CVPresentationTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t CVPresentationTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t CVPresentationTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t CVPresentationTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t CVPresentationTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
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

RTC::ReturnCode_t CVPresentationTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t CVPresentationTest::onAborting(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t CVPresentationTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t CVPresentationTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t CVPresentationTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t CVPresentationTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool CVPresentationTest::runTest()
{
    return true;
}


extern "C"
{
 
  void CVPresentationTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(cvpresentation_spec);
    manager->registerFactory(profile,
                             RTC::Create<CVPresentationTest>,
                             RTC::Delete<CVPresentationTest>);
  }
  
}
