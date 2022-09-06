// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  ConsoleInString.cpp
 * @brief Console string input component
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#include <iostream>
#include <string>

#include "ConsoleInString.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const consoleinstring_spec[] =
#else
static const char* consoleinstring_spec[] =
#endif
  {
    "implementation_id", "ConsoleInString",
    "type_name",         "ConsoleInString",
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
ConsoleInString::ConsoleInString(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_StringOut("String", m_String)
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ConsoleInString::~ConsoleInString()
{
}



RTC::ReturnCode_t ConsoleInString::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("String", m_StringOut);

  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ConsoleInString::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t ConsoleInString::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInString::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInString::onActivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInString::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * コンソールから入力された文字列をOutPortのStringから出力する。
 */

RTC::ReturnCode_t ConsoleInString::onExecute(RTC::UniqueId /*ec_id*/)
{
	std::string st;

	std::cout << "Input string: " << std::flush;
	std::getline(std::cin, st);
	m_String.data = st.c_str();
	setTimestamp(m_String);
	m_StringOut.write();
	std::cout << "Output: " << m_String.data << std::endl;

	return RTC::RTC_OK;
}


//RTC::ReturnCode_t ConsoleInString::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInString::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInString::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInString::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t ConsoleInString::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}



extern "C"
{
 
  void ConsoleInStringInit(RTC::Manager* manager)
  {
    coil::Properties profile(consoleinstring_spec);
    manager->registerFactory(profile,
                             RTC::Create<ConsoleInString>,
                             RTC::Delete<ConsoleInString>);
  }
  
}
