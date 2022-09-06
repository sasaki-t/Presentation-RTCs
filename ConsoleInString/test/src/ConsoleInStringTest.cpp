// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  ConsoleInStringTest.cpp
 * @brief Console string input component (test code)
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#include "ConsoleInStringTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const consoleinstring_spec[] =
#else
static const char* consoleinstring_spec[] =
#endif
  {
    "implementation_id", "ConsoleInStringTest",
    "type_name",         "ConsoleInStringTest",
    "description",       "Console string input component",
    "version",           "1.1.0",
    "vendor",            "TakeshiSasaki",
    "category",          "example",
    "activity_type",     "SPORADIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ConsoleInStringTest::ConsoleInStringTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_StringIn("String", m_String)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ConsoleInStringTest::~ConsoleInStringTest()
{
}



RTC::ReturnCode_t ConsoleInStringTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("String", m_StringIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ConsoleInStringTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t ConsoleInStringTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInStringTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInStringTest::onActivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInStringTest::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * コンソールから入力された文字列をOutPortのStringから出力する。
 */

RTC::ReturnCode_t ConsoleInStringTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t ConsoleInStringTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInStringTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInStringTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInStringTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInStringTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool ConsoleInStringTest::runTest()
{
    return true;
}


extern "C"
{
 
  void ConsoleInStringTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(consoleinstring_spec);
    manager->registerFactory(profile,
                             RTC::Create<ConsoleInStringTest>,
                             RTC::Delete<ConsoleInStringTest>);
  }
  
}
