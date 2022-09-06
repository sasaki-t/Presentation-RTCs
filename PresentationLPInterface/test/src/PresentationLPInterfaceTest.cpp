// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  PresentationLPInterfaceTest.cpp
 * @brief Create slide change and draw commands for presentation component based on laser light pointing (test code)
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#include "PresentationLPInterfaceTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const presentationlpinterface_spec[] =
#else
static const char* presentationlpinterface_spec[] =
#endif
  {
    "implementation_id", "PresentationLPInterfaceTest",
    "type_name",         "PresentationLPInterfaceTest",
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
PresentationLPInterfaceTest::PresentationLPInterfaceTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_ImageOut("Image", m_Image),
    m_BgUpdateTriggerOut("BgUpdateTrigger", m_BgUpdateTrigger),
    m_SlideRelativeCommandIn("SlideRelativeCommand", m_SlideRelativeCommand),
    m_DrawPositionsIn("DrawPositions", m_DrawPositions),
    m_SlideSizeInfoPortPort("SlideSizeInfoPort")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PresentationLPInterfaceTest::~PresentationLPInterfaceTest()
{
}



RTC::ReturnCode_t PresentationLPInterfaceTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("SlideRelativeCommand", m_SlideRelativeCommandIn);
  addInPort("DrawPositions", m_DrawPositionsIn);
  
  // Set OutPort buffer
  addOutPort("Image", m_ImageOut);
  addOutPort("BgUpdateTrigger", m_BgUpdateTriggerOut);
  
  // Set service provider to Ports
  m_SlideSizeInfoPortPort.registerProvider("SlideSizeInfo", "Slide::SlideSizeInfo", m_SlideSizeInfo);
  
  // Set service consumers to Ports
  
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
RTC::ReturnCode_t PresentationLPInterfaceTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t PresentationLPInterfaceTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationLPInterfaceTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t PresentationLPInterfaceTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationLPInterfaceTest::onDeactivated(RTC::UniqueId /*ec_id*/)
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

RTC::ReturnCode_t PresentationLPInterfaceTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationLPInterfaceTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationLPInterfaceTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationLPInterfaceTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationLPInterfaceTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationLPInterfaceTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool PresentationLPInterfaceTest::runTest()
{
    return true;
}


extern "C"
{
 
  void PresentationLPInterfaceTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentationlpinterface_spec);
    manager->registerFactory(profile,
                             RTC::Create<PresentationLPInterfaceTest>,
                             RTC::Delete<PresentationLPInterfaceTest>);
  }
  
}
