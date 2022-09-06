// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  PresentationKeyDecoderTest.cpp
 * @brief Create slide change commands for presentation component based on input data (test code)
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#include "PresentationKeyDecoderTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const presentationkeydecoder_spec[] =
#else
static const char* presentationkeydecoder_spec[] =
#endif
  {
    "implementation_id", "PresentationKeyDecoderTest",
    "type_name",         "PresentationKeyDecoderTest",
    "description",       "Create slide change commands for presentation component based on input data",
    "version",           "1.1.0",
    "vendor",            "TakeshiSasaki",
    "category",          "Presentation",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.Next", "10,13,32,110",
    "conf.default.Previous", "8,112",
    "conf.default.Reload", "99,114",

    // Widget
    "conf.__widget__.Next", "text",
    "conf.__widget__.Previous", "text",
    "conf.__widget__.Reload", "text",
    // Constraints

    "conf.__type__.Next", "std::vector<int>",
    "conf.__type__.Previous", "std::vector<int>",
    "conf.__type__.Reload", "std::vector<int>",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PresentationKeyDecoderTest::PresentationKeyDecoderTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_KeyOut("Key", m_Key),
    m_SlideRelativeCommandIn("SlideRelativeCommand", m_SlideRelativeCommand)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PresentationKeyDecoderTest::~PresentationKeyDecoderTest()
{
}



RTC::ReturnCode_t PresentationKeyDecoderTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("SlideRelativeCommand", m_SlideRelativeCommandIn);
  
  // Set OutPort buffer
  addOutPort("Key", m_KeyOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("Next", m_Next, "10,13,32,110");
  bindParameter("Previous", m_Previous, "8,112");
  bindParameter("Reload", m_Reload, "99,114");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PresentationKeyDecoderTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t PresentationKeyDecoderTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationKeyDecoderTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t PresentationKeyDecoderTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationKeyDecoderTest::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * InPortのKeyから文字を読み込み、コンフィギュレーションで指定した
 * 文字コードに相当する文字が得られた場合に、プレゼンテーションコン
 * ポーネントのスライドページ変更コマンドに対応する数値をOutPortの
 * SlideRelativeCommandから出力する。
 */

RTC::ReturnCode_t PresentationKeyDecoderTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationKeyDecoderTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationKeyDecoderTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationKeyDecoderTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationKeyDecoderTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationKeyDecoderTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool PresentationKeyDecoderTest::runTest()
{
    return true;
}


extern "C"
{
 
  void PresentationKeyDecoderTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentationkeydecoder_spec);
    manager->registerFactory(profile,
                             RTC::Create<PresentationKeyDecoderTest>,
                             RTC::Delete<PresentationKeyDecoderTest>);
  }
  
}
