// -*- C++ -*-
/*!
 * @file  PresentationCommentTimer.h
 * @brief Timer component for presentation component
 * @date  $Date$
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#ifndef PRESENTATIONCOMMENTTIMER_H
#define PRESENTATIONCOMMENTTIMER_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <string>
#include <ctime>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
 * @class PresentationCommentTimer
 * @brief Timer component for presentation component
 *
 * プレゼンテーション用の時間計測コンポーネント。InPortのMeasureme
 * ntTriggerにデータが入力される度にコンフィギュレーションのOutput
 * Typeで指定された形式で計測結果をOutPortのMeasuredTimeStringから
 * 出力する。
 *
 * InPort
 * ポート名/型/説明
 * MeasurementTrigger/TimedShort/アクティブ化後に初めて何かデータが
 * 入力された場合、計測を開始する。また、何かデータが入力される度に
 * コンフィギュレーションのOutputTypeで指定された形式で計測結果をO
 * utPortのMeasuredTimeStringから出力する。
 * OutPort
 * ポート名/型/説明
 * MeasuredTimeString/TimedString/コンフィギュレーションのOutputTy
 * peで指定される出力形式に応じて以下のように計測時間を文字列にした
 * もの。
 * lapの場合: lap_time
 * splitの場合: split_time
 * (コンフィギュレーションのPresentationTimeに正の値が指定されてい
 * る場合は split_time/presentation_time)
 * split+lapの場合: split_time (lap_time)
 * (コンフィギュレーションのPresentationTimeに正の値が指定されてい
 * る場合は split_time/presentation_time (lap_time))
 * remainingの場合: remaining_time
 * remaining+lapの場合: remaining_time (lap_time)
 *
 */
class PresentationCommentTimer
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  PresentationCommentTimer(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~PresentationCommentTimer();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   * 初期化を行う。
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   * InPortのMeasurementTriggerにデータが入力される度にコンフィギュ
   * レーションのOutputTypeで指定された形式で計測結果をOutPortのMe
   * asuredTimeStringから出力する。
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * OutPortのMeasuredTimeStringからの結果の出力形式。lapの場合はラ
   * ップタイム（前の出力からの経過時間）、splitの場合はスプリット
   * タイム（計測開始からの累計時間）、split+lapの場合はスプリット
   * タイムとラップタイム、remainingの場合は残り時間（コンフィギュ
   * レーションのPresentationTimeから計測開始からの累計時間を引いた
   * もの）、remaining+lapの場合は残り時間とラップタイム。
   * - Name: OutputType OutputType
   * - DefaultValue: split
   * - Constraint: (lap, split, split+lap, remaining,
   *               remaining+lap)
   */
  std::string m_OutputType;
  /*!
   * プレゼンテーションの時間。コンフィギュレーションのOutputTypeで
   * 指定される出力形式がremainingまたはremaining+lapの場合には、こ
   * の時間から計測開始からの累計時間を引いたものが出力される。また
   * 、この値が正で、出力形式がsplitまたはsplit+lapの場合、累積時間
   * に加え、この時間も出力される。
   * - Name: PresentationTime PresentationTime
   * - DefaultValue: 0.0
   * - Unit: minute
   */
  double m_PresentationTime;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  TimedShort m_MeasurementTrigger;
  /*!
   * アクティブ化後に初めて何かデータが入力された場合、計測を開始す
   * る。また、何かデータが入力される度にコンフィギュレーションのO
   * utputTypeで指定された形式で計測結果をOutPortのMeasuredTimeStr
   * ingから出力する。
   * - Type: TimedShort
   * - Number: 1
   */
  InPort<TimedShort> m_MeasurementTriggerIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  TimedString m_MeasuredTimeString;
  /*!
   * コンフィギュレーションのOutputTypeで指定される出力形式に応じて
   * 以下のように計測時間を文字列にしたもの。
   * lapの場合: lap_time
   * splitの場合: split_time
   * (コンフィギュレーションのPresentationTimeに正の値が指定されて
   * いる場合は split_time/presentation_time)
   * split+lapの場合: split_time (lap_time)
   * (コンフィギュレーションのPresentationTimeに正の値が指定されて
   * いる場合は split_time/presentation_time (lap_time))
   * remainingの場合: remaining_time
   * remaining+lapの場合: remaining_time (lap_time)
   * - Type: TimedStirng
   */
  OutPort<TimedString> m_MeasuredTimeStringOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  bool start;
  std::time_t start_time;
  std::time_t previous_time;
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void PresentationCommentTimerInit(RTC::Manager* manager);
};

#endif // PRESENTATIONCOMMENTTIMER_H
