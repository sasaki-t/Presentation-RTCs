// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  CVPresentation.h
 * @brief Presentation component using OpenCV
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#ifndef CVPRESENTATION_H
#define CVPRESENTATION_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include "slides.h"
#include "commentmanager.h"

// Service implementation headers
// <rtc-template block="service_impl_h">
#include "SlideSizeSVC_impl.h"

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
 * @class CVPresentation
 * @brief Presentation component using OpenCV
 *
 * OpenCVを用いたプレゼンテーションコンポーネント。
 * 読み込むスライドはOpenCVで読み込める画像形式で作成し、通し番号を
 * つけておく。
 * 例）test1.jpg, test2.jpg, ...
 * 読み込むスライドやその他設定はコンフィギュレーションから指定する
 * 。
 * スライドのページ送りはInPortのSlideNumberに値を入力することで行
 * う。
 * また、InPortのPenやCommentに値を入力することで、スライド内に線を
 * 引いたり、コメントを表示したりすることが可能。
 * さらに、スライドのページが変更された場合のスライド番号および、ス
 * ライド上で操作したマウスイベントとキーボード入力はOutPortから出
 * 力される。
 *
 * InPort
 * ポート名/型/説明
 * SlideNumberIn/TimedShort/表示するスライドの番号。コンフィギュレ
 * ーションを指定すれば、スライドの絶対番号(例:
 * test003.jpgの場合は3)で指定することも、現在のスライドからの相対
 * 的な番号で指定することも可能。
 * Pen/TimedShortSeq/スライドに表示する線分・点の座標(x1,y1),
 * (x2,y2),...。コンフィギュレーションで指定されたパラメータで、座
 * 標が2点以上の場合は指定された座標の間に線分を、座標が1点のみの場
 * 合はその座標に点を描画する。
 * Comment/TimedString/スライドに表示するコメント（テキスト）。文字
 * の大きさやサイズはコメントにコマンドを含めることで指定することが
 * 可能。指定がない場合はコンフィギュレーションで指定されたパラメー
 * タで表示する。有効なのは半角英数字のみ。
 * OutPort
 * ポート名/型/説明
 * SlideNumberOut/TimedShort/現在のスライド番号。スライド番号が変更
 * された場合に出力される。
 * Key/TimedChar/スライドのウインドウがアクティブのときにキーボード
 * から入力された値。
 * MouseEvent/TimedShortSeq/スライド上で発生したマウスイベント(CV_
 * EVENT_*:
 * 左ボタンが押された、など)、その座標(x,y)、フラグ(CV_EVENT_FLAG_
 * *: 左ボタンが押されている、など)。
 * ServicePort
 * ポート名:SlideSizeInfoPort
 * インタフェース名/方向/説明
 * SlideSizeInfo/Provided/スライドの画像の幅と高さを取得するための
 * インタフェース。
 *
 */
// </rtc-template>
class CVPresentation
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  CVPresentation(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~CVPresentation() override;

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
   * 終了処理を行う。
   *
   * The deactivated action (Active state exit action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id) override;

  /***
   * InPortのSlideNumberInに入力された値に応じてスライドのページを
   * 変更する。また、その際には新たなスライド番号をOutPortのSlideN
   * umberOutから出力する。
   * InPortのPenに入力された座標に線を引く。
   * InPortのCommentに入力された文字列を表示する。
   * スライド上で操作したマウスイベントとキーボード入力をOutPortか
   * ら出力する。
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
   * 終了処理を行う。
   *
   * The aborting action when main logic error occurred.
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id) override;

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
   * スライドが保存されているパス。
   * - Name: SlideFilePath SlideFilePath
   * - DefaultValue: ../../../tutorial
   */
  std::string m_SlideFilePath;
  /*!
   * スライドの名前。通し番号の部分はアスタリスク(*)としておく。例
   * えば、スライドが"test1.jpg", "test2.jpg", ..., "test10.jpg",
   * ...の場合には"test*.jpg"を指定する。スライドが"test001.jpg",
   * "test002.jpg", ..., "test010.jpg",
   * ...のように通し番号が最低3桁で表されている場合は"test***.jpg"
   * を指定する。
   * なお、スライドはOpenCVでサポートされている画像形式である必要が
   * ある。
   * - Name: SlideFileName SlideFileName
   * - DefaultValue: tutorial***.png
   */
  std::string m_SlideFileName;
  /*!
   * スライド番号の初期値。例えば、最初のスライドが"test1.jpg"の場
   * 合には1を指定する。
   * - Name: SlideFileInitialNumber SlideFileInitialNumber
   * - DefaultValue: 1
   * - Constraint: x>=0
   */
  int m_SlideFileInitialNumber;
  /*!
   * InPortのSlideNumberInからスライド番号をスライドの絶対番号(例:
   * test3.jpgの場合は3)で指定する場合は0、現在のスライドからの相対
   * 的な番号で指定する場合は1。
   * - Name: SlideNumberInRelative SlideNumberInRelative
   * - DefaultValue: 1
   * - Constraint: 0または1
   */
  int m_SlideNumberInRelative;
  /*!
   * 表示するスライドの幅。SlideSizeWidthとSlideSizeHeightがともに
   * 0の場合、元々の画像サイズでスライドを表示する。一方が正で他方
   * が0の場合は、正の値のみを利用し、元の画像と同じアスペクト比に
   * なるようにスライドを表示する。
   * - Name: SlideSizeWidth SlideSizeWidth
   * - DefaultValue: 0
   * - Unit: pixel
   * - Constraint: x>=0
   */
  int m_SlideSizeWidth;
  /*!
   * 表示するスライドの高さ。SlideSizeWidthとSlideSizeHeightがとも
   * に0の場合、元々の画像サイズでスライドを表示する。一方が正で他
   * 方が0の場合は、正の値のみを利用し、元の画像と同じアスペクト比
   * になるようにスライドを表示する。
   * - Name: SlideSizeHeight SlideSizeHeight
   * - DefaultValue: 0
   * - Unit: pixel
   * - Constraint: x>=0
   */
  int m_SlideSizeHeight;
  /*!
   * コメントの文字の色(RGB)のデフォルト値。
   * - Name: CommentColorRGB CommentColorRGB
   * - DefaultValue: 0,0,0
   */
  std::vector<int> m_CommentColorRGB;
  /*!
   * コメントの文字の大きさ（スケール）のデフォルト値。
   * - Name: CommentSize CommentSize
   * - DefaultValue: 1.0
   * - Constraint: x>0
   */
  double m_CommentSize;
  /*!
   * コメントの文字が流れる基本速度。
   * - Name: CommentBaseSpeed CommentBaseSpeed
   * - DefaultValue: 4
   * - Constraint: x>0
   */
  int m_CommentBaseSpeed;
  /*!
   * ペンの色(RGB)。
   * - Name: PenColorRGB PenColorRGB
   * - DefaultValue: 255,0,0
   */
  std::vector<int> m_PenColorRGB;
  /*!
   * ペンの太さ。
   * - Name: PenThickness PenThickness
   * - DefaultValue: 4
   * - Constraint: x>0
   */
  int m_PenThickness;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedShort m_SlideNumberIn;
  /*!
   * 表示するスライドの番号。
   * コンフィギュレーションを指定すれば、スライドの絶対番号(例:
   * test003.jpgの場合は3)で指定することも、現在のスライドからの相
   * 対的な番号で指定することも可能。
   * - Type: TimedShort
   * - Number: 1
   */
  RTC::InPort<RTC::TimedShort> m_SlideNumberInIn;
  RTC::TimedShortSeq m_Pen;
  /*!
   * スライドに表示する線分・点の座標(x1,y1), (x2,y2),...。
   * コンフィギュレーションで指定されたパラメータで、座標が2点以上
   * の場合は指定された座標の間に線分を、座標が1点のみの場合はその
   * 座標に点を描画する。
   * - Type: TimedShortSeq
   * - Number: 偶数
   */
  RTC::InPort<RTC::TimedShortSeq> m_PenIn;
  RTC::TimedString m_Comment;
  /*!
   * スライドに表示するコメント（テキスト）。文字の大きさやサイズは
   * コメントにコマンドを含めることで指定することが可能。指定がない
   * 場合はコンフィギュレーションで指定されたパラメータで表示する。
   * 有効なのは半角英数字のみ。
   * - Type: TimedString
   */
  RTC::InPort<RTC::TimedString> m_CommentIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedShort m_SlideNumberOut;
  /*!
   * 現在のスライド番号。スライド番号が変更された場合に出力される。
   * - Type: TimedShort
   * - Number: 1
   */
  RTC::OutPort<RTC::TimedShort> m_SlideNumberOutOut;
  RTC::TimedChar m_Key;
  /*!
   * スライドのウインドウがアクティブのときにキーボードから入力され
   * た値。
   * - Type: TimedChar
   * - Number: 1
   */
  RTC::OutPort<RTC::TimedChar> m_KeyOut;
  RTC::TimedShortSeq m_MouseEvent;
  /*!
   * スライド上で発生したマウスイベント(CV_EVENT_*:
   * 左ボタンが押された、など)、その座標(x,y)、フラグ(CV_EVENT_FLA
   * G_*: 左ボタンが押されている、など)。
   * - Type: TimedShortSeq
   * - Number: 4
   */
  RTC::OutPort<RTC::TimedShortSeq> m_MouseEventOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  /*!
   */
  RTC::CorbaPort m_SlideSizeInfoPortPort;
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  /*!
   * スライドの画像の幅と高さを取得するためのインタフェース。
   * short getWidth(); //スライドの画像の幅を取得
   * short getHeight(); //スライドの画像の高さを取得
   * - Argument:      なし
   * - Return Value:  スライドの幅または高さ
   * - PreCondition:  コンポーネントをアクティブ化し、スライドを正
   *                  しく読み込んだ後に有効。
   */
  Slide_SlideSizeInfoSVC_impl m_SlideSizeInfo;
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>


 private:
  // <rtc-template block="private_attribute">
	 Slides slds;
	 CommentManager cmtMgr;
	 std::string window_name;
	 cv::Mat display_img; //slide with comments  

  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void CVPresentationInit(RTC::Manager* manager);
};

#endif // CVPRESENTATION_H
