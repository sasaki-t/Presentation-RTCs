// -*- C++ -*-
/*!
 * @file  PresentationKeyDecoder.cpp
 * @brief Create slide change commands for presentation component based on input data
 * @date $Date$
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#include <iostream>

#include "VectorConvert.h"
#include "PresentationKeyDecoder.h"

// Module specification
// <rtc-template block="module_spec">
static const char* presentationkeydecoder_spec[] =
  {
    "implementation_id", "PresentationKeyDecoder",
    "type_name",         "PresentationKeyDecoder",
    "description",       "Create slide change commands for presentation component based on input data",
    "version",           "1.0.0",
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
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PresentationKeyDecoder::PresentationKeyDecoder(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_KeyIn("Key", m_Key),
    m_SlideRelativeCommandOut("SlideRelativeCommand", m_SlideRelativeCommand)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PresentationKeyDecoder::~PresentationKeyDecoder()
{
}



RTC::ReturnCode_t PresentationKeyDecoder::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Key", m_KeyIn);
  
  // Set OutPort buffer
  addOutPort("SlideRelativeCommand", m_SlideRelativeCommandOut);
  
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
RTC::ReturnCode_t PresentationKeyDecoder::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationKeyDecoder::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationKeyDecoder::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t PresentationKeyDecoder::onActivated(RTC::UniqueId ec_id)
{
  while(m_KeyIn.isNew()){
    m_KeyIn.read();
  }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PresentationKeyDecoder::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * InPortのKeyから文字を読み込み、コンフィギュレーションで指定した
 * 文字コードに相当する文字が得られた場合に、プレゼンテーションコン
 * ポーネントのスライドページ変更コマンドに対応する数値をOutPortの
 * SlideRelativeCommandから出力する。
 */

RTC::ReturnCode_t PresentationKeyDecoder::onExecute(RTC::UniqueId ec_id)
{
  unsigned int i;
  int k;
  int res;
  bool found = false;

  if(m_KeyIn.isNew()){
    m_KeyIn.read();
    k = (int)m_Key.data;
    std::cout << "Input: " << m_Key.data << std::endl;

    for(i=0;i<m_Next.size();i++){ //serch Next
      if(m_Next[i]==k){ //if found
        res = 1; //set "Next" command
        found = true;
        break;
      }
	}
    if(!found){
      for(i=0;i<m_Previous.size();i++){ //serch Previous
        if(m_Previous[i]==k){ //if found
          res = -1; //set "Previous" command
          found = true;
          break;
        }
	  }
	}
    if(!found){
      for(i=0;i<m_Reload.size();i++){ //serch Reload
        if(m_Reload[i]==k){ //if found
          res = 0; //set "Reload" command
          found = true;
          break;
        }
	  }
	}

    //Output
	if(found){
      m_SlideRelativeCommand.data = res;
      std::cout << "-> Command: " << m_SlideRelativeCommand.data << std::endl;
      setTimestamp(m_SlideRelativeCommand);
	  m_SlideRelativeCommandOut.write();
    }

  }//endif(m_KeyIn.isNew())

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PresentationKeyDecoder::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationKeyDecoder::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationKeyDecoder::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationKeyDecoder::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationKeyDecoder::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void PresentationKeyDecoderInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentationkeydecoder_spec);
    manager->registerFactory(profile,
                             RTC::Create<PresentationKeyDecoder>,
                             RTC::Delete<PresentationKeyDecoder>);
  }
  
};


