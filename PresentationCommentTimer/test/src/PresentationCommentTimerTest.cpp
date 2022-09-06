// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  PresentationCommentTimerTest.cpp
 * @brief Timer component for presentation component (test code)
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#include "PresentationCommentTimerTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const presentationcommenttimer_spec[] =
#else
static const char* presentationcommenttimer_spec[] =
#endif
  {
    "implementation_id", "PresentationCommentTimerTest",
    "type_name",         "PresentationCommentTimerTest",
    "description",       "Timer component for presentation component",
    "version",           "1.1.0",
    "vendor",            "TakeshiSasaki",
    "category",          "Presentation",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.OutputType", "split",
    "conf.default.PresentationTime", "0.0",

    // Widget
    "conf.__widget__.OutputType", "radio",
    "conf.__widget__.PresentationTime", "text",
    // Constraints
    "conf.__constraints__.OutputType", "(lap,split,split+lap,remaining,remaining+lap)",

    "conf.__type__.OutputType", "string",
    "conf.__type__.PresentationTime", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PresentationCommentTimerTest::PresentationCommentTimerTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_MeasurementTriggerOut("MeasurementTrigger", m_MeasurementTrigger),
    m_MeasuredTimeStringIn("MeasuredTimeString", m_MeasuredTimeString)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PresentationCommentTimerTest::~PresentationCommentTimerTest()
{
}



RTC::ReturnCode_t PresentationCommentTimerTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("MeasuredTimeString", m_MeasuredTimeStringIn);
  
  // Set OutPort buffer
  addOutPort("MeasurementTrigger", m_MeasurementTriggerOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("OutputType", m_OutputType, "split");
  bindParameter("PresentationTime", m_PresentationTime, "0.0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PresentationCommentTimerTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t PresentationCommentTimerTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationCommentTimerTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t PresentationCommentTimerTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationCommentTimerTest::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * InPortのMeasurementTriggerにデータが入力される度にコンフィギュレ
 * ーションのOutputTypeで指定された形式で計測結果をOutPortのMeasur
 * edTimeStringから出力する。
 */

RTC::ReturnCode_t PresentationCommentTimerTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t PresentationCommentTimerTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationCommentTimerTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationCommentTimerTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationCommentTimerTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t PresentationCommentTimerTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool PresentationCommentTimerTest::runTest()
{
    return true;
}


extern "C"
{
 
  void PresentationCommentTimerTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentationcommenttimer_spec);
    manager->registerFactory(profile,
                             RTC::Create<PresentationCommentTimerTest>,
                             RTC::Delete<PresentationCommentTimerTest>);
  }
  
}
