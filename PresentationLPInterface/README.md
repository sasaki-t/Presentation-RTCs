# PresentationLPInterface

## Overview

Create slide change and draw commands for presentation component based on laser light pointing

## Description

カメラコンポーネントと併用することで、レーザポインタによるスライドページの変更とスライド内への描画を行う。ただし、カメラはスライドを表示しているスクリーンやディスプレイをz=c（一定）の平面とし、表示されているスライドの左上を(0,0,c)、右下を(slide_width,slide_height,c)としてキャリブレーションされているものとする。InPortのImageから読み込んだ画像から、輝度が閾値以上大きくなった点を検出候補点とし、最も明るく変化した点をレーザポインタで指されたスライド上の位置を認識する。さらに、その位置に応じてプレゼンテーションコンポーネントのスライドページ変更コマンドとペン描画位置に対応する数値をOutPortのSlideRelativeCommandとDrawPositionsからそれぞれ出力する。

### Input and Output

InPort<br/>ポート名/型/説明<br/>Image/TimedCameraImage/入力画像及び座標変換のためのカメラパラメータ。<br/>BgUpdateTrigger/TimedShort/何かデータが入力された場合、背景画像を更新する。<br/>OutPort<br/>ポート名/型/説明<br/>SlideRelativeCommand/TimedShort/スライドのページを変更するためのコマンドに対応する数値。<br/>DrawPositions/TimedShortSeq/ペンで描画する位置に対応する数値。<br/>ServicePort<br/>ポート名:SlideSizeInfoPort<br/>インタフェース名/方向/説明<br/>SlideSizeInfo/Required/スライドの画像の幅と高さを取得するためのインタフェース。

### Algorithm etc



### Basic Information

|  |  |
----|---- 
| Module Name | PresentationLPInterface |
| Description | Create slide change and draw commands for presentation component based on laser light pointing |
| Version | 1.0.0 |
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
    <td>on_deactivated</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td rowspan="4">on_execute</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td>InPortのImageから読み込んだ画像から、スライド上のレーザポインタで指された位置を認識し、その位置に応じてプレゼンテーションコンポーネントのスライドページ変更コマンドとペン描画位置に対応する数値をOutPortのSlideRelativeCommandとDrawPositionsからそれぞれ出力する。</td>
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
    <td>on_aborting</td>
    <td colspan="2"></td>
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

#### Image

入力画像及び座標変換のためのカメラパラメータ。

<table>
  <tr>
    <td>DataType</td>
    <td>Img::TimedCameraImage</td>
    <td>TimedCameraImage</td>
  </tr>
  <tr>
    <td>IDL file</td>
    <td colspan="2">CameraCommonInterface.idl</td>
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

#### BgUpdateTrigger

何かデータが入力された場合、背景画像を更新する。

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


### OutPorts definition

#### SlideRelativeCommand

スライドのページを変更するためのコマンドに対応する数値。コンフィギュレーションのSlideChangeAreaとSlideChangeAreaSizeで指定された領域にSlideChangeCount回以上点が検出された場合に、SlideChangeArea内の位置に応じて-1,0,1のいずれかを出力する。

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

#### DrawPositions

検出された点の中で最も輝度の差が高い点の位置(x,y)。コンフィギュレーションのDetectUpdateTime以内に新たに点が検出された場合は移動を続けているものと考え、1ステップ前の位置と現在の位置(x_old, y_old, x_now, y_now)の2点を出力する。

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
    <td colspan="2">2または4</td>
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
      <td>Consumer</td>
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
      <td></td>
    </tr>
    <tr>
      <td>Return Value</td>
      <td></td>
    </tr>
    <tr>
      <td>Exception</td>
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
</table>


### Configuration definition

#### DetectLuminanceDiff

入力画像のある点の輝度が背景画像のその点の輝度よりもこの値以上大きい場合、検出の候補点となる。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>30</td>
    <td>30</td>
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

#### DetectBgUpdate

閾値処理で得られた候補点の数がこの値以上の場合、背景は大きく変化してしまっているものと考え、背景を更新する。ただし、この値が負の場合は、何点検出されても背景を更新しない。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>5</td>
    <td>5</td>
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

#### DetectUpdateTime

最新の検出から次の検出までの時間がこの値以下の場合、2つの点は連続したものとして考える。<br/>（毎ステップ確実に検出できるとは限らないため、プレゼンテーションコンポーネントで線を描画した場合に途切れ途切れになることを避ける等の目的で使用。）


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">double</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>0.5</td>
    <td>0.5</td>
  </tr>
  <tr>
    <td>Unit</td>
    <td>sec</td>
    <td>sec</td>
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

#### ScreenZ

スクリーン平面のz座標。スクリーンをz=(一定)の平面と考え、単眼カメラで位置を出すために使用。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">double</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>0.0</td>
    <td>0.0</td>
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

#### SlideChangeArea

スライドのページを変更するためのコマンドを生成する領域を定義する。この値がtopの場合は画像の上端、leftの場合は画像の左端、rightの場合は画像の右端、bottomの場合は画像の下端を基準とし、コンフィギュレーションのSlideChangeAreaSizeで指定された範囲までの領域（例えば、SlideChangeAreaがtop、SlideChangeAreaSizeが10なら画像の上端から10画素の範囲、つまり10×画像幅の矩形領域）を範囲とする。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">string</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>top</td>
    <td>top</td>
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
    <td>(top,left,right,bottom)</td>
    <td>(top,left,right,bottom)</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### SlideChangeAreaSize

スライドのページを変更するためのコマンドを生成する領域を定義する。コンフィギュレーションのSlideChangeAreaがtopの場合は画像の上端、leftの場合は画像の左端、rightの場合は画像の右端、bottomの場合は画像の下端を基準とし、この値で指定された範囲までの領域（例えば、SlideChangeAreaがtop、SlideChangeAreaSizeが10なら画像の上端から10画素の範囲、つまり10×画像幅の矩形領域）を範囲とする。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>50</td>
    <td>50</td>
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
    <td>x>0</td>
    <td>x>0</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### SlideChangeCount

コンフィギュレーションのSlideChangeAreaとSlideChangeAreaSizeで指定された領域のある部分でSlideChangeCount回以上連続して点が検出された場合に、スライドを変更するコマンドを生成する。<br/>命令の種類は、領域の左側1/3（SlideChangeAreaがtopまたはbottomのとき）または上側1/3（leftまたはrightのとき）で検出された場合は前のスライドへ戻すコマンド(=-1)、中央1/3で検出された場合はスライドの現在のページを再読み込みするコマンド(=0)、右側1/3（SlideChangeAreaがtopまたはbottomのとき）または下側1/3（leftまたはrightのとき）で検出された場合はスライドを次のページへ進めるコマンド(=1)とする。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>5</td>
    <td>5</td>
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

#### SlideChangeWait

このコンポーネントによってスライドが変更されたとき、この時間だけ何もせずに待つ。<br/>（スライドの変更が連続して起こったり、スライド変更直後の不要な描画を避けるため。）


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
    <td>sec</td>
    <td>sec</td>
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
