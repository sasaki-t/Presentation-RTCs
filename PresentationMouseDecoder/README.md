# PresentationMouseDecoder

## Overview

Create slide change and draw commands for presentation component based on input mouse data

## Description

InPortのMouseEventから値を読み込み、プレゼンテーションコンポーネントのスライドページ変更コマンドとペン描画位置に対応する数値をOutPortのSlideRelativeCommandとDrawPositionsからそれぞれ出力する。

### Input and Output

InPort<br/>ポート名/型/説明<br/>MouseEvent/TimedShortSeq/マウスイベント(CV_EVENT_*: 左ボタンが押された、など)、その座標(x,y)、フラグ(CV_EVENT_FLAG_*: 左ボタンが押されている、など)。<br/>OutPort<br/>ポート名/型/説明<br/>SlideRelativeCommand/TimedShort/スライドのページを変更するためのコマンドに対応する数値。<br/>DrawPositions/TimedShortSeq/ペンで描画する位置に対応する数値。

### Algorithm etc



### Basic Information

|  |  |
----|---- 
| Module Name | PresentationMouseDecoder |
| Description | Create slide change and draw commands for presentation component based on input mouse data |
| Version | 1.1.0 |
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
      <td>InPortのMouseEventから値を読み込み、プレゼンテーションコンポーネントのスライドページ変更コマンドとペン描画位置に対応する数値をOutPortのSlideRelativeCommandとDrawPositionsからそれぞれ出力する。</td>
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

#### MouseEvent

マウスイベント(CV_EVENT_*: 左ボタンが押された、など)、その座標(x,y)、フラグ(CV_EVENT_FLAG_*: 左ボタンが押されている、など)。

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


### OutPorts definition

#### SlideRelativeCommand

スライドのページを変更するためのコマンドに対応する数値。コンフィギュレーションのSlideChangeClickが1の場合、InPortのMouseEventへの入力が左クリックに相当するときは1,右クリックに相当するときは-1。コンフィギュレーションのSlideChangeClickが2の場合、InPortのMouseEventへの入力が左ダブルクリックに相当するときは1,右ダブルクリックに相当するときは-1。

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

InPortのMouseEventへの入力が左クリックを押しながらのマウス移動に相当する場合の位置(x,y)。移動を続けている場合は、1ステップ前の位置と現在の位置(x_old, y_old, x_now, y_now)の2点を出力する。

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


### Configuration definition

#### SlideChangeClick

この値が1の場合、左シングルクリックに相当するマウスイベントが入力されたときにスライドを次のページへ進めるコマンド(=1)を出力し、右シングルクリックに相当するマウスイベントが入力されたときにスライドを前のページへ戻すコマンド(=-1)を出力する。この値が2の場合、シングルクリックではなくダブルクリックの場合に上記と同様の出力となる。


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
    <td>(1,2)</td>
    <td>(1,2)</td>
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
