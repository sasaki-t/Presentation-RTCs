# CVPresentation

## Overview

Presentation component using OpenCV

## Description

OpenCVを用いたプレゼンテーションコンポーネント。<br/>読み込むスライドはOpenCVで読み込める画像形式で作成し、通し番号をつけておく。<br/>例）test1.jpg, test2.jpg, ...<br/>読み込むスライドやその他設定はコンフィギュレーションから指定する。<br/>スライドのページ送りはInPortのSlideNumberに値を入力することで行う。<br/>また、InPortのPenやCommentに値を入力することで、スライド内に線を引いたり、コメントを表示したりすることが可能。<br/>さらに、スライドのページが変更された場合のスライド番号および、スライド上で操作したマウスイベントとキーボード入力はOutPortから出力される。

### Input and Output

InPort<br/>ポート名/型/説明<br/>SlideNumberIn/TimedShort/表示するスライドの番号。コンフィギュレーションを指定すれば、スライドの絶対番号(例: test003.jpgの場合は3)で指定することも、現在のスライドからの相対的な番号で指定することも可能。<br/>Pen/TimedShortSeq/スライドに表示する線分・点の座標(x1,y1), (x2,y2),...。コンフィギュレーションで指定されたパラメータで、座標が2点以上の場合は指定された座標の間に線分を、座標が1点のみの場合はその座標に点を描画する。<br/>Comment/TimedString/スライドに表示するコメント（テキスト）。文字の大きさやサイズはコメントにコマンドを含めることで指定することが可能。指定がない場合はコンフィギュレーションで指定されたパラメータで表示する。有効なのは半角英数字のみ。<br/>OutPort<br/>ポート名/型/説明<br/>SlideNumberOut/TimedShort/現在のスライド番号。スライド番号が変更された場合に出力される。<br/>Key/TimedChar/スライドのウインドウがアクティブのときにキーボードから入力された値。<br/>MouseEvent/TimedShortSeq/スライド上で発生したマウスイベント(CV_EVENT_*: 左ボタンが押された、など)、その座標(x,y)、フラグ(CV_EVENT_FLAG_*: 左ボタンが押されている、など)。<br/>ServicePort<br/>ポート名:SlideSizeInfoPort<br/>インタフェース名/方向/説明<br/>SlideSizeInfo/Provided/スライドの画像の幅と高さを取得するためのインタフェース。

### Algorithm etc



### Basic Information

|  |  |
----|---- 
| Module Name | CVPresentation |
| Description | Presentation component using OpenCV |
| Version | 1.2.0 |
| Vendor | TakeshiSasaki |
| Category | Presentation |
| Comp. Type | COMMUTATIVE |
| Act. Type | PERIODIC |
| Kind | DataFlowComponent |
| MAX Inst. | 0 |

### Activity definition

<table>
  <tr>
    <td rowspan="4">on_initialize</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td>on_finalize</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_startup</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_shutdown</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td rowspan="4">on_activated</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td>初期化を行う。</td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td rowspan="4">on_deactivated</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td>終了処理を行う。</td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td rowspan="4">on_execute</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td>InPortのSlideNumberInに入力された値に応じてスライドのページを変更する。また、その際には新たなスライド番号をOutPortのSlideNumberOutから出力する。<br/>InPortのPenに入力された座標に線を引く。<br/>InPortのCommentに入力された文字列を表示する。<br/>スライド上で操作したマウスイベントとキーボード入力をOutPortから出力する。</td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td rowspan="4">on_aborting</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td>終了処理を行う。</td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td>on_error</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_reset</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_state_update</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_rate_changed</td>
    <td colspan="2"></td>
  </tr>
</table>

### InPorts definition

#### SlideNumberIn

表示するスライドの番号。<br/>コンフィギュレーションを指定すれば、スライドの絶対番号(例: test003.jpgの場合は3)で指定することも、現在のスライドからの相対的な番号で指定することも可能。

<table>
  <tr>
    <td>DataType</td>
    <td>RTC::TimedShort</td>
    <td>TimedShort</td>
  </tr>
  <tr>
    <td>IDL file</td>
    <td colspan="2">BasicDataType.idl</td>
  </tr>
  <tr>
    <td>Number of Data</td>
    <td colspan="2">1</td>
  </tr>
  <tr>
    <td>Semantics</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Unit</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Occirrence frecency Period</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Operational frecency Period</td>
    <td colspan="2"></td>
  </tr>
</table>

#### Pen

スライドに表示する線分・点の座標(x1,y1), (x2,y2),...。<br/>コンフィギュレーションで指定されたパラメータで、座標が2点以上の場合は指定された座標の間に線分を、座標が1点のみの場合はその座標に点を描画する。

<table>
  <tr>
    <td>DataType</td>
    <td>RTC::TimedShortSeq</td>
    <td>TimedShortSeq</td>
  </tr>
  <tr>
    <td>IDL file</td>
    <td colspan="2">BasicDataType.idl</td>
  </tr>
  <tr>
    <td>Number of Data</td>
    <td colspan="2">偶数</td>
  </tr>
  <tr>
    <td>Semantics</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Unit</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Occirrence frecency Period</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Operational frecency Period</td>
    <td colspan="2"></td>
  </tr>
</table>

#### Comment

スライドに表示するコメント（テキスト）。文字の大きさやサイズはコメントにコマンドを含めることで指定することが可能。指定がない場合はコンフィギュレーションで指定されたパラメータで表示する。有効なのは半角英数字のみ。

<table>
  <tr>
    <td>DataType</td>
    <td>RTC::TimedString</td>
    <td>TimedString</td>
  </tr>
  <tr>
    <td>IDL file</td>
    <td colspan="2">BasicDataType.idl</td>
  </tr>
  <tr>
    <td>Number of Data</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Semantics</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Unit</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Occirrence frecency Period</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Operational frecency Period</td>
    <td colspan="2"></td>
  </tr>
</table>


### OutPorts definition

#### SlideNumberOut

現在のスライド番号。スライド番号が変更された場合に出力される。

<table>
  <tr>
    <td>DataType</td>
    <td>RTC::TimedShort</td>
    <td>TimedShort</td>
  </tr>
  <tr>
    <td>IDL file</td>
    <td colspan="2">BasicDataType.idl</td>
  </tr>
  <tr>
    <td>Number of Data</td>
    <td colspan="2">1</td>
  </tr>
  <tr>
    <td>Semantics</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Unit</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Occirrence frecency Period</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Operational frecency Period</td>
    <td colspan="2"></td>
  </tr>
</table>

#### Key

スライドのウインドウがアクティブのときにキーボードから入力された値。

<table>
  <tr>
    <td>DataType</td>
    <td>RTC::TimedChar</td>
    <td>TimedChar</td>
  </tr>
  <tr>
    <td>IDL file</td>
    <td colspan="2">BasicDataType.idl</td>
  </tr>
  <tr>
    <td>Number of Data</td>
    <td colspan="2">1</td>
  </tr>
  <tr>
    <td>Semantics</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Unit</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Occirrence frecency Period</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Operational frecency Period</td>
    <td colspan="2"></td>
  </tr>
</table>

#### MouseEvent

スライド上で発生したマウスイベント(CV_EVENT_*: 左ボタンが押された、など)、その座標(x,y)、フラグ(CV_EVENT_FLAG_*: 左ボタンが押されている、など)。

<table>
  <tr>
    <td>DataType</td>
    <td>RTC::TimedShortSeq</td>
    <td>TimedShortSeq</td>
  </tr>
  <tr>
    <td>IDL file</td>
    <td colspan="2">BasicDataType.idl</td>
  </tr>
  <tr>
    <td>Number of Data</td>
    <td colspan="2">4</td>
  </tr>
  <tr>
    <td>Semantics</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Unit</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Occirrence frecency Period</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Operational frecency Period</td>
    <td colspan="2"></td>
  </tr>
</table>


### Service Port definition

#### SlideSizeInfoPort



<table>
  <tr>
    <td>I/F Description</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td colspan="3">Interface</td>
  </tr>
  <tr>
    <td rowspan="9">SlideSizeInfo</td>
    <td>Type</td>
    <td>Slide::SlideSizeInfo</td>
    <tr>
      <td>Direction</td>
      <td>Provider</td>
    </tr>
    <tr>
      <td>Description</td>
      <td>スライドの画像の幅と高さを取得するためのインタフェース。<br/>short getWidth(); //スライドの画像の幅を取得<br/>short getHeight(); //スライドの画像の高さを取得</td>
    </tr>
    <tr>
      <td>IDL file</td>
      <td>SlideSize.idl</td>
    </tr>
    <tr>
      <td>Argument</td>
      <td>なし</td>
    </tr>
    <tr>
      <td>Return Value</td>
      <td>スライドの幅または高さ</td>
    </tr>
    <tr>
      <td>Exception</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td>コンポーネントをアクティブ化し、スライドを正しく読み込んだ後に有効。</td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
</table>


### Configuration definition

#### SlideFilePath

スライドが保存されているパス。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">string</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>../../../tutorial</td>
    <td>./</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### SlideFileName

スライドの名前。通し番号の部分はアスタリスク(*)としておく。例えば、スライドが"test1.jpg", "test2.jpg", ..., "test10.jpg", ...の場合には"test*.jpg"を指定する。スライドが"test001.jpg", "test002.jpg", ..., "test010.jpg", ...のように通し番号が最低3桁で表されている場合は"test***.jpg"を指定する。<br/><br/>なお、スライドはOpenCVでサポートされている画像形式である必要がある。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">string</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>tutorial***.png</td>
    <td>test***.jpg</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### SlideFileInitialNumber

スライド番号の初期値。例えば、最初のスライドが"test1.jpg"の場合には1を指定する。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>1</td>
    <td>1</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td>x>=0</td>
    <td>x>=0</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### SlideNumberInRelative

InPortのSlideNumberInからスライド番号をスライドの絶対番号(例: test3.jpgの場合は3)で指定する場合は0、現在のスライドからの相対的な番号で指定する場合は1。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>1</td>
    <td>1</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">radio</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td>(0,1)</td>
    <td>0または1</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### SlideSizeWidth

表示するスライドの幅。SlideSizeWidthとSlideSizeHeightがともに0の場合、元々の画像サイズでスライドを表示する。一方が正で他方が0の場合は、正の値のみを利用し、元の画像と同じアスペクト比になるようにスライドを表示する。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>0</td>
    <td>0</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td>pixel</td>
    <td>pixel</td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td>x>=0</td>
    <td>x>=0</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### SlideSizeHeight

表示するスライドの高さ。SlideSizeWidthとSlideSizeHeightがともに0の場合、元々の画像サイズでスライドを表示する。一方が正で他方が0の場合は、正の値のみを利用し、元の画像と同じアスペクト比になるようにスライドを表示する。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>0</td>
    <td>0</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td>pixel</td>
    <td>pixel</td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td>x>=0</td>
    <td>x>=0</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### CommentColorRGB

コメントの文字の色(RGB)のデフォルト値。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">std::vector<int></td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>0,0,0</td>
    <td>0,0,0</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### CommentSize

コメントの文字の大きさ（スケール）のデフォルト値。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">double</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>1.0</td>
    <td>1.0</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td>x>0</td>
    <td>x>0</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### CommentBaseSpeed

コメントの文字が流れる基本速度。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>4</td>
    <td>4</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td>x>0</td>
    <td>x>0</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### PenColorRGB

ペンの色(RGB)。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">std::vector<int></td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>255,0,0</td>
    <td>255,0,0</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### PenThickness

ペンの太さ。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>4</td>
    <td>4</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td>x>0</td>
    <td>x>0</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>


## Demo

## Requirement

## Setup

### Windows

### Ubuntu

## Usage

## Running the tests

## LICENCE




## References




## Author

佐々木毅 (Takeshi SASAKI)<br/>sasaki-t(_at_)ieee.org
