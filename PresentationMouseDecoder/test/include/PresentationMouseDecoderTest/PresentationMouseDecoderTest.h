// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  PresentationMouseDecoderTest.h
 * @brief Create slide change and draw commands for presentation component based on input mouse data (test code)
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#ifndef PRESENTATIONMOUSEDECODER_TEST__H
#define PRESENTATIONMOUSEDECODER_TEST_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

/*!
 * @class PresentationMouseDecoderTest
 * @brief Create slide change and draw commands for presentation component based on input mouse data
 *
 */
class PresentationMouseDecoderTest
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  PresentationMouseDecoderTest(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~PresentationMouseDecoderTest() override;

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  // <rtc-template block="activity">
  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onInitialize() override;

  /***
   *
   * The finalize action (on ALIVE->END transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onFinalize() override;

  /***
   *
   * The startup action when ExecutionContext startup
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id) override;

  /***
   *
   * The shutdown action when ExecutionContext stop
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id) override;

  /***
   * 初期化を行う。
   *
   * The activated action (Active state entry action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The deactivated action (Active state exit action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id) override;

  /***
   * InPortのMouseEventから値を読み込み、プレゼンテーションコンポー
   * ネントのスライドページ変更コマンドとペン描画位置に対応する数値
   * をOutPortのSlideRelativeCommandとDrawPositionsからそれぞれ出力
   * する。
   *
   * The execution action that is invoked periodically
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id) override;

  /***
   *
   * The aborting action when main logic error occurred.
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id) override;

  /***
   *
   * The error action in ERROR state
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onError(RTC::UniqueId ec_id) override;

  /***
   *
   * The reset action that is invoked resetting
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onReset(RTC::UniqueId ec_id) override;
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id) override;

  /***
   *
   * The action that is invoked when execution context's rate is changed
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id) override;
  // </rtc-template>

  bool runTest();

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
  RTC::TimedShort m_SlideRelativeCommand;
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
  RTC::InPort<RTC::TimedShort> m_SlideRelativeCommandIn;
  RTC::TimedShortSeq m_DrawPositions;
  /*!
   * InPortのMouseEventへの入力が左クリックを押しながらのマウス移動
   * に相当する場合の位置(x,y)。移動を続けている場合は、1ステップ前
   * の位置と現在の位置(x_old, y_old, x_now,
   * y_now)の2点を出力する。
   * - Type: TimedShortSeq
   * - Number: 2または4
   */
  RTC::InPort<RTC::TimedShortSeq> m_DrawPositionsIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedShortSeq m_MouseEvent;
  /*!
   * マウスイベント(CV_EVENT_*:
   * 左ボタンが押された、など)、その座標(x,y)、フラグ(CV_EVENT_FLA
   * G_*: 左ボタンが押されている、など)。
   * - Type: TimedShortSeq
   * - Number: 4
   */
  RTC::OutPort<RTC::TimedShortSeq> m_MouseEventOut;
  
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
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void PresentationMouseDecoderTestInit(RTC::Manager* manager);
};

#endif // PRESENTATIONMOUSEDECODER_TEST_H
