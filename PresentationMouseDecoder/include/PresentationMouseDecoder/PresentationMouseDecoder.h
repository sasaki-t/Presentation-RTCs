// -*- C++ -*-
/*!
 * @file  PresentationMouseDecoder.h
 * @brief Create slide change and draw commands for presentation component based on input mouse data
 * @date  $Date$
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#ifndef PRESENTATIONMOUSEDECODER_H
#define PRESENTATIONMOUSEDECODER_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
 * @class PresentationMouseDecoder
 * @brief Create slide change and draw commands for presentation component based on input mouse data
 *
 * InPortのMouseEventから値を読み込み、プレゼンテーションコンポーネ
 * ントのスライドページ変更コマンドとペン描画位置に対応する数値をO
 * utPortのSlideRelativeCommandとDrawPositionsからそれぞれ出力する
 * 。
 *
 * InPort
 * ポート名/型/説明
 * MouseEvent/TimedShortSeq/マウスイベント(CV_EVENT_*:
 * 左ボタンが押された、など)、その座標(x,y)、フラグ(CV_EVENT_FLAG_
 * *: 左ボタンが押されている、など)。
 * OutPort
 * ポート名/型/説明
 * SlideRelativeCommand/TimedShort/スライドのページを変更するための
 * コマンドに対応する数値。
 * DrawPositions/TimedShortSeq/ペンで描画する位置に対応する数値。
 *
 */
class PresentationMouseDecoder
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  PresentationMouseDecoder(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~PresentationMouseDecoder();

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
   * InPortのMouseEventから値を読み込み、プレゼンテーションコンポー
   * ネントのスライドページ変更コマンドとペン描画位置に対応する数値
   * をOutPortのSlideRelativeCommandとDrawPositionsからそれぞれ出力
   * する。
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
   * この値が1の場合、左シングルクリックに相当するマウスイベントが
   * 入力されたときにスライドを次のページへ進めるコマンド(=1)を出力
   * し、右シングルクリックに相当するマウスイベントが入力されたとき
   * にスライドを前のページへ戻すコマンド(=-1)を出力する。この値が
   * 2の場合、シングルクリックではなくダブルクリックの場合に上記と
   * 同様の出力となる。
   * - Name: SlideChangeClick SlideChangeClick
   * - DefaultValue: 1
   * - Constraint: (1,2)
   */
  int m_SlideChangeClick;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  TimedShortSeq m_MouseEvent;
  /*!
   * マウスイベント(CV_EVENT_*:
   * 左ボタンが押された、など)、その座標(x,y)、フラグ(CV_EVENT_FLA
   * G_*: 左ボタンが押されている、など)。
   * - Type: TimedShortSeq
   * - Number: 4
   */
  InPort<TimedShortSeq> m_MouseEventIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  TimedShort m_SlideRelativeCommand;
  /*!
   * スライドのページを変更するためのコマンドに対応する数値。コンフ
   * ィギュレーションのSlideChangeClickが1の場合、InPortのMouseEve
   * ntへの入力が左クリックに相当するときは1,右クリックに相当すると
   * きは-1。コンフィギュレーションのSlideChangeClickが2の場合、In
   * PortのMouseEventへの入力が左ダブルクリックに相当するときは1,右
   * ダブルクリックに相当するときは-1。
   * - Type: TimedShort
   * - Number: 1
   */
  OutPort<TimedShort> m_SlideRelativeCommandOut;
  TimedShortSeq m_DrawPositions;
  /*!
   * InPortのMouseEventへの入力が左クリックを押しながらのマウス移動
   * に相当する場合の位置(x,y)。移動を続けている場合は、1ステップ前
   * の位置と現在の位置(x_old, y_old, x_now,
   * y_now)の2点を出力する。
   * - Type: TimedShortSeq
   * - Number: 2または4
   */
  OutPort<TimedShortSeq> m_DrawPositionsOut;
  
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
  int x_old;
  int y_old;

  int click_type; //1: left button down, -1: right button down
  int click_x;
  int click_y;
  int click_d; //total displacement after button down
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void PresentationMouseDecoderInit(RTC::Manager* manager);
};

#endif // PRESENTATIONMOUSEDECODER_H
