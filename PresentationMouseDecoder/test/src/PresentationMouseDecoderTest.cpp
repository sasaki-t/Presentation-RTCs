// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  PresentationMouseDecoderTest.cpp
 * @brief Create slide change and draw commands for presentation component based on input mouse data (test code)
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#include "PresentationMouseDecoderTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const presentationmousedecoder_spec[] =
#else
static const char* presentationmousedecoder_spec[] =
#endif
  {
    "implementation_id", "PresentationMouseDecoderTest",
    "type_name",         "PresentationMouseDecoderTest",
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
PresentationMouseDecoderTest::PresentationMouseDecoderTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_MouseEventOut("MouseEvent", m_MouseEvent),
    m_SlideRelativeCommandIn("SlideRelativeCommand", m_SlideRelativeCommand),
    m_DrawPositionsIn("DrawPositions", m_DrawPositions)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PresentationMouseDecoderTest::~PresentationMouseDecoderTest()
{
}



RTC::ReturnCode_t PresentationMouseDecoderTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("SlideRelativeCommand", m_SlideRelativeCommandIn);
  addInPort("DrawPositions", m_DrawPositionsIn);
  
  // Set OutPort buffer
  addOutPort("MouseEvent", m_MouseEventOut);
  
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
RTC::ReturnCode_t PresentationMouseDecoderTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t PresentationMouseDecoderTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationMouseDecoderTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t PresentationMouseDecoderTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationMouseDecoderTest::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * InPortのMouseEventから値を読み込み、プレゼンテーションコンポーネ
 * ントのスライドページ変更コマンドとペン描画位置に対応する数値をO
 * utPortのSlideRelativeCommandとDrawPositionsからそれぞれ出力する
 * 。
 */

RTC::ReturnCode_t PresentationMouseDecoderTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationMouseDecoderTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationMouseDecoderTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationMouseDecoderTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationMouseDecoderTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationMouseDecoderTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool PresentationMouseDecoderTest::runTest()
{
    return true;
}


extern "C"
{
 
  void PresentationMouseDecoderTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentationmousedecoder_spec);
    manager->registerFactory(profile,
                             RTC::Create<PresentationMouseDecoderTest>,
                             RTC::Delete<PresentationMouseDecoderTest>);
  }
  
}
