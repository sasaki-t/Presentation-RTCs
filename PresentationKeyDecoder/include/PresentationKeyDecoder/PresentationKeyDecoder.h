// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  PresentationKeyDecoder.h
 * @brief Create slide change commands for presentation component based on input data
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#ifndef PRESENTATIONKEYDECODER_H
#define PRESENTATIONKEYDECODER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <vector>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>


// <rtc-template block="component_description">
/*!
 * @class PresentationKeyDecoder
 * @brief Create slide change commands for presentation component based on input data
 *
 * InPortのKeyから文字を読み込み、コンフィギュレーションで指定した
 * 文字コードに相当する文字が得られた場合に、プレゼンテーションコン
 * ポーネントのスライドページ変更コマンドに対応する数値をOutPortの
 * SlideRelativeCommandから出力する。
 *
 * InPort
 * ポート名/型/説明
 * Key/TimedChar/入力文字。
 * OutPort
 * ポート名/型/説明
 * SlideRelativeCommand/TimedShort/スライドのページを変更するための
 * コマンドに対応する数値。InPortのKeyへの入力文字がコンフィギュレ
 * ーションのNextのいずれかに一致するときは1,Previousのいずれかに一
 * 致するときは-1,Reloadのいずれかに一致するときは0。同じ文字コード
 * が複数のコンフィギュレーションで指定されていた場合、優先順位はN
 * ext,Previous,Reloadの順となる。
 *
 */
// </rtc-template>
class PresentationKeyDecoder
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  PresentationKeyDecoder(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~PresentationKeyDecoder() override;

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
   * InPortのKeyから文字を読み込み、コンフィギュレーションで指定し
   * た文字コードに相当する文字が得られた場合に、プレゼンテーション
   * コンポーネントのスライドページ変更コマンドに対応する数値をOut
   * PortのSlideRelativeCommandから出力する。
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


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * ここに書かれた文字コードに相当する文字が入力されたときにスライ
   * ドを次のページへ進めるコマンド(=1)を出力する。
   * - Name: Next Next
   * - DefaultValue: 10,13,32,110
   */
  std::vector<int> m_Next;
  /*!
   * ここに書かれた文字コードに相当する文字が入力されたときにスライ
   * ドを前のページへ戻すコマンド(=-1)を出力する。
   * - Name: Previous Previous
   * - DefaultValue: 8,112
   */
  std::vector<int> m_Previous;
  /*!
   * ここに書かれた文字コードに相当する文字が入力されたときにスライ
   * ドの現在のページを再読み込みするコマンド(=0)を出力する。
   * - Name: Reload Reload
   * - DefaultValue: 99,114
   */
  std::vector<int> m_Reload;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedChar m_Key;
  /*!
   * 入力文字。
   * - Type: TimedChar
   * - Number: 1
   */
  RTC::InPort<RTC::TimedChar> m_KeyIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedShort m_SlideRelativeCommand;
  /*!
   * スライドのページを変更するためのコマンドに対応する数値。InPor
   * tのKeyへの入力文字がコンフィギュレーションのNextのいずれかに一
   * 致するときは1,Previousのいずれかに一致するときは-1,Reloadのい
   * ずれかに一致するときは0。同じ文字コードが複数のコンフィギュレ
   * ーションで指定されていた場合、優先順位はNext,Previous,Reloadの
   * 順となる。
   * - Type: TimedShort
   * - Number: 1
   */
  RTC::OutPort<RTC::TimedShort> m_SlideRelativeCommandOut;
  
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
  DLL_EXPORT void PresentationKeyDecoderInit(RTC::Manager* manager);
};

#endif // PRESENTATIONKEYDECODER_H
