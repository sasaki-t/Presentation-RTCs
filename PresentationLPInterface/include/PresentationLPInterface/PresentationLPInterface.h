// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  PresentationLPInterface.h
 * @brief Create slide change and draw commands for presentation component based on laser light pointing
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#ifndef PRESENTATIONLPINTERFACE_H
#define PRESENTATIONLPINTERFACE_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <string>
#include "lp_detector.h"

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "SlideSizeStub.h"
#include "CameraCommonInterfaceStub.h"
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>


// <rtc-template block="component_description">
/*!
 * @class PresentationLPInterface
 * @brief Create slide change and draw commands for presentation component based on laser light pointing
 *
 * カメラコンポーネントと併用することで、レーザポインタによるスライ
 * ドページの変更とスライド内への描画を行う。ただし、カメラはスライ
 * ドを表示しているスクリーンやディスプレイをz=c（一定）の平面とし
 * 、表示されているスライドの左上を(0,0,c)、右下を(slide_width,sli
 * de_height,c)としてキャリブレーションされているものとする。InPor
 * tのImageから読み込んだ画像から、輝度が閾値以上大きくなった点を検
 * 出候補点とし、最も明るく変化した点をレーザポインタで指されたスラ
 * イド上の位置を認識する。さらに、その位置に応じてプレゼンテーショ
 * ンコンポーネントのスライドページ変更コマンドとペン描画位置に対応
 * する数値をOutPortのSlideRelativeCommandとDrawPositionsからそれぞ
 * れ出力する。
 *
 * InPort
 * ポート名/型/説明
 * Image/TimedCameraImage/入力画像及び座標変換のためのカメラパラメ
 * ータ。
 * BgUpdateTrigger/TimedShort/何かデータが入力された場合、背景画像
 * を更新する。
 * OutPort
 * ポート名/型/説明
 * SlideRelativeCommand/TimedShort/スライドのページを変更するための
 * コマンドに対応する数値。
 * DrawPositions/TimedShortSeq/ペンで描画する位置に対応する数値。
 * ServicePort
 * ポート名:SlideSizeInfoPort
 * インタフェース名/方向/説明
 * SlideSizeInfo/Required/スライドの画像の幅と高さを取得するための
 * インタフェース。
 *
 */
// </rtc-template>
class PresentationLPInterface
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  PresentationLPInterface(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~PresentationLPInterface() override;

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
   * InPortのImageから読み込んだ画像から、スライド上のレーザポイン
   * タで指された位置を認識し、その位置に応じてプレゼンテーションコ
   * ンポーネントのスライドページ変更コマンドとペン描画位置に対応す
   * る数値をOutPortのSlideRelativeCommandとDrawPositionsからそれぞ
   * れ出力する。
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
   * 入力画像のある点の輝度が背景画像のその点の輝度よりもこの値以上
   * 大きい場合、検出の候補点となる。
   * - Name: DetectLuminanceDiff DetectLuminanceDiff
   * - DefaultValue: 30
   */
  int m_DetectLuminanceDiff;
  /*!
   * 閾値処理で得られた候補点の数がこの値以上の場合、背景は大きく変
   * 化してしまっているものと考え、背景を更新する。ただし、この値が
   * 負の場合は、何点検出されても背景を更新しない。
   * - Name: DetectBgUpdate DetectBgUpdate
   * - DefaultValue: 5
   */
  int m_DetectBgUpdate;
  /*!
   * 最新の検出から次の検出までの時間がこの値以下の場合、2つの点は
   * 連続したものとして考える。
   * （毎ステップ確実に検出できるとは限らないため、プレゼンテーショ
   * ンコンポーネントで線を描画した場合に途切れ途切れになることを避
   * ける等の目的で使用。）
   * - Name: DetectUpdateTime DetectUpdateTime
   * - DefaultValue: 0.5
   * - Unit: sec
   * - Constraint: x>=0
   */
  double m_DetectUpdateTime;
  /*!
   * スクリーン平面のz座標。スクリーンをz=(一定)の平面と考え、単眼
   * カメラで位置を出すために使用。
   * - Name: ScreenZ ScreenZ
   * - DefaultValue: 0.0
   */
  double m_ScreenZ;
  /*!
   * スライドのページを変更するためのコマンドを生成する領域を定義す
   * る。この値がtopの場合は画像の上端、leftの場合は画像の左端、ri
   * ghtの場合は画像の右端、bottomの場合は画像の下端を基準とし、コ
   * ンフィギュレーションのSlideChangeAreaSizeで指定された範囲まで
   * の領域（例えば、SlideChangeAreaがtop、SlideChangeAreaSizeが10
   * なら画像の上端から10画素の範囲、つまり10×画像幅の矩形領域）を
   * 範囲とする。
   * - Name: SlideChangeArea SlideChangeArea
   * - DefaultValue: top
   * - Constraint: (top,left,right,bottom)
   */
  std::string m_SlideChangeArea;
  /*!
   * スライドのページを変更するためのコマンドを生成する領域を定義す
   * る。コンフィギュレーションのSlideChangeAreaがtopの場合は画像の
   * 上端、leftの場合は画像の左端、rightの場合は画像の右端、bottom
   * の場合は画像の下端を基準とし、この値で指定された範囲までの領域
   * （例えば、SlideChangeAreaがtop、SlideChangeAreaSizeが10なら画
   * 像の上端から10画素の範囲、つまり10×画像幅の矩形領域）を範囲と
   * する。
   * - Name: SlideChangeAreaSize SlideChangeAreaSize
   * - DefaultValue: 50
   * - Unit: pixel
   * - Constraint: x>0
   */
  int m_SlideChangeAreaSize;
  /*!
   * コンフィギュレーションのSlideChangeAreaとSlideChangeAreaSizeで
   * 指定された領域のある部分でSlideChangeCount回以上連続して点が検
   * 出された場合に、スライドを変更するコマンドを生成する。
   * 命令の種類は、領域の左側1/3（SlideChangeAreaがtopまたはbottom
   * のとき）または上側1/3（leftまたはrightのとき）で検出された場合
   * は前のスライドへ戻すコマンド(=-1)、中央1/3で検出された場合はス
   * ライドの現在のページを再読み込みするコマンド(=0)、右側1/3（Sl
   * ideChangeAreaがtopまたはbottomのとき）または下側1/3（leftまた
   * はrightのとき）で検出された場合はスライドを次のページへ進める
   * コマンド(=1)とする。
   * - Name: SlideChangeCount SlideChangeCount
   * - DefaultValue: 5
   * - Constraint: x>0
   */
  int m_SlideChangeCount;
  /*!
   * このコンポーネントによってスライドが変更されたとき、この時間だ
   * け何もせずに待つ。
   * （スライドの変更が連続して起こったり、スライド変更直後の不要な
   * 描画を避けるため。）
   * - Name: SlideChangeWait SlideChangeWait
   * - DefaultValue: 1.0
   * - Unit: sec
   * - Constraint: x>=0
   */
  double m_SlideChangeWait;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  Img::TimedCameraImage m_Image;
  /*!
   * 入力画像及び座標変換のためのカメラパラメータ。
   * - Type: TimedCameraImage
   * - Number: 1
   */
  RTC::InPort<Img::TimedCameraImage> m_ImageIn;
  RTC::TimedShort m_BgUpdateTrigger;
  /*!
   * 何かデータが入力された場合、背景画像を更新する。
   * - Type: TimedShort
   * - Number: 1
   */
  RTC::InPort<RTC::TimedShort> m_BgUpdateTriggerIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedShort m_SlideRelativeCommand;
  /*!
   * スライドのページを変更するためのコマンドに対応する数値。コンフ
   * ィギュレーションのSlideChangeAreaとSlideChangeAreaSizeで指定さ
   * れた領域にSlideChangeCount回以上点が検出された場合に、SlideCh
   * angeArea内の位置に応じて-1,0,1のいずれかを出力する。
   * - Type: TimedShort
   * - Number: 1
   */
  RTC::OutPort<RTC::TimedShort> m_SlideRelativeCommandOut;
  RTC::TimedShortSeq m_DrawPositions;
  /*!
   * 検出された点の中で最も輝度の差が高い点の位置(x,y)。コンフィギ
   * ュレーションのDetectUpdateTime以内に新たに点が検出された場合は
   * 移動を続けているものと考え、1ステップ前の位置と現在の位置(x_o
   * ld, y_old, x_now, y_now)の2点を出力する。
   * - Type: TimedShortSeq
   * - Number: 2または4
   */
  RTC::OutPort<RTC::TimedShortSeq> m_DrawPositionsOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  /*!
   */
  RTC::CorbaPort m_SlideSizeInfoPortPort;
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  /*!
   * スライドの画像の幅と高さを取得するためのインタフェース。
   * short getWidth(); //スライドの画像の幅を取得
   * short getHeight(); //スライドの画像の高さを取得
   */
  RTC::CorbaConsumer<Slide::SlideSizeInfo> m_SlideSizeInfo;
  
  // </rtc-template>


 private:
  // <rtc-template block="private_attribute">
	 LPDetector lpd;
	 bool bg_update; //if true, update background
	 int area_index;
	 int area_count;

	 RTC::Time time_old; //previously detected time
	 cv::Point ptSc_old; //point detected in the previous time
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void PresentationLPInterfaceInit(RTC::Manager* manager);
};

#endif // PRESENTATIONLPINTERFACE_H
