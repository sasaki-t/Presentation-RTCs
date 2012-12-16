// -*- C++ -*-
/*!
 * @file  PresentationCommentTimer.cpp
 * @brief Timer component for presentation component
 * @date $Date$
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#include <iostream>
#include <string>
#include <ctime>

#include "PresentationCommentTimer.h"
#include "time_to_string.h"

// Module specification
// <rtc-template block="module_spec">
static const char* presentationcommenttimer_spec[] =
  {
    "implementation_id", "PresentationCommentTimer",
    "type_name",         "PresentationCommentTimer",
    "description",       "Timer component for presentation component",
    "version",           "1.0.0",
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
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PresentationCommentTimer::PresentationCommentTimer(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_MeasurementTriggerIn("MeasurementTrigger", m_MeasurementTrigger),
    m_MeasuredTimeStringOut("MeasuredTimeString", m_MeasuredTimeString)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PresentationCommentTimer::~PresentationCommentTimer()
{
}



RTC::ReturnCode_t PresentationCommentTimer::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("MeasurementTrigger", m_MeasurementTriggerIn);
  
  // Set OutPort buffer
  addOutPort("MeasuredTimeString", m_MeasuredTimeStringOut);
  
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
RTC::ReturnCode_t PresentationCommentTimer::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationCommentTimer::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationCommentTimer::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t PresentationCommentTimer::onActivated(RTC::UniqueId ec_id)
{
  start = false;

  while(m_MeasurementTriggerIn.isNew()){
    m_MeasurementTriggerIn.read();
  }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PresentationCommentTimer::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * InPortのMeasurementTriggerにデータが入力される度にコンフィギュレ
 * ーションのOutputTypeで指定された形式で計測結果をOutPortのMeasur
 * edTimeStringから出力する。
 */

RTC::ReturnCode_t PresentationCommentTimer::onExecute(RTC::UniqueId ec_id)
{
  std::string st;
  std::time_t current_time;
  double lap, split, remain;

  if(m_MeasurementTriggerIn.isNew()){
    m_MeasurementTriggerIn.read();
    if(!start){ //initialize if first time
      start = true;
      std::time(&start_time);
      previous_time = start_time;
	}

    //calculate lap, split, and remaining time
    time(&current_time);
	lap = std::difftime(current_time, previous_time);
	split = std::difftime(current_time, start_time);
	remain = m_PresentationTime*60 - split;
    previous_time = current_time; //update previous time

	if(m_OutputType == "lap"){ //lap time only
      st = convert_timediff_to_hms(lap);
    }else if(m_OutputType == "split"){ //split time
      st = convert_timediff_to_hms(split);
	  if(m_PresentationTime>0){ //add expected total time if necessary
        st.push_back('/');
        st += convert_timediff_to_hms(m_PresentationTime*60);
	  }
    }else if(m_OutputType == "split+lap"){ //split time and lap time
      st = convert_timediff_to_hms(split);
	  if(m_PresentationTime>0){ //add expected total time if necessary
        st.push_back('/');
        st += convert_timediff_to_hms(m_PresentationTime*60);
      }
      st += " (" + convert_timediff_to_hms(lap) + ")"; //add lap time
    }else if(m_OutputType == "remaining"){ //remaining time only
      st = convert_timediff_to_hms(remain);
    }else if(m_OutputType == "remaining+lap"){ //remaining time and lap time
      st = convert_timediff_to_hms(remain);
      st += " (" + convert_timediff_to_hms(lap) + ")"; //add lap time
    }else{
      std::cerr << "Invalid argument: OutputType" << std::endl;
      return RTC::RTC_OK;
    }

    setTimestamp(m_MeasuredTimeString);
    m_MeasuredTimeString.data = st.c_str();
    m_MeasuredTimeStringOut.write();
  } //end if(m_MeasurementTriggerIn.isNew())

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PresentationCommentTimer::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationCommentTimer::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationCommentTimer::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationCommentTimer::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationCommentTimer::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void PresentationCommentTimerInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentationcommenttimer_spec);
    manager->registerFactory(profile,
                             RTC::Create<PresentationCommentTimer>,
                             RTC::Delete<PresentationCommentTimer>);
  }
  
};


