# PresentationCommentTimer

## Overview

Timer component for presentation component

## Description

プレゼンテーション用の時間計測コンポーネント。InPortのMeasurementTriggerにデータが入力される度にコンフィギュレーションのOutputTypeで指定された形式で計測結果をOutPortのMeasuredTimeStringから出力する。

### Input and Output

InPort<br/>ポート名/型/説明<br/>MeasurementTrigger/TimedShort/アクティブ化後に初めて何かデータが入力された場合、計測を開始する。また、何かデータが入力される度にコンフィギュレーションのOutputTypeで指定された形式で計測結果をOutPortのMeasuredTimeStringから出力する。<br/>OutPort<br/>ポート名/型/説明<br/>MeasuredTimeString/TimedString/コンフィギュレーションのOutputTypeで指定される出力形式に応じて以下のように計測時間を文字列にしたもの。<br/>lapの場合: lap_time<br/>splitの場合: split_time<br/>(コンフィギュレーションのPresentationTimeに正の値が指定されている場合は split_time/presentation_time)<br/>split+lapの場合: split_time (lap_time)<br/>(コンフィギュレーションのPresentationTimeに正の値が指定されている場合は split_time/presentation_time (lap_time))<br/>remainingの場合: remaining_time<br/>remaining+lapの場合: remaining_time (lap_time)

### Algorithm etc



### Basic Information

|  |  |
----|---- 
| Module Name | PresentationCommentTimer |
| Description | Timer component for presentation component |
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
      <td>InPortのMeasurementTriggerにデータが入力される度にコンフィギュレーションのOutputTypeで指定された形式で計測結果をOutPortのMeasuredTimeStringから出力する。</td>
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

#### MeasurementTrigger

アクティブ化後に初めて何かデータが入力された場合、計測を開始する。また、何かデータが入力される度にコンフィギュレーションのOutputTypeで指定された形式で計測結果をOutPortのMeasuredTimeStringから出力する。

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

#### MeasuredTimeString

コンフィギュレーションのOutputTypeで指定される出力形式に応じて以下のように計測時間を文字列にしたもの。<br/>lapの場合: lap_time<br/>splitの場合: split_time<br/>(コンフィギュレーションのPresentationTimeに正の値が指定されている場合は split_time/presentation_time)<br/>split+lapの場合: split_time (lap_time)<br/>(コンフィギュレーションのPresentationTimeに正の値が指定されている場合は split_time/presentation_time (lap_time))<br/>remainingの場合: remaining_time<br/>remaining+lapの場合: remaining_time (lap_time)

<table>
  <tr>
    <td>DataType</td>
    <td>RTC::TimedString</td>
    <td>TimedStirng</td>
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


### Service Port definition


### Configuration definition

#### OutputType

OutPortのMeasuredTimeStringからの結果の出力形式。lapの場合はラップタイム（前の出力からの経過時間）、splitの場合はスプリットタイム（計測開始からの累計時間）、split+lapの場合はスプリットタイムとラップタイム、remainingの場合は残り時間（コンフィギュレーションのPresentationTimeから計測開始からの累計時間を引いたもの）、remaining+lapの場合は残り時間とラップタイム。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">string</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>split</td>
    <td>split</td>
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
    <td>(lap,split,split+lap,remaining,remaining+lap)</td>
    <td>(lap, split, split+lap, remaining, remaining+lap)</td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### PresentationTime

プレゼンテーションの時間。コンフィギュレーションのOutputTypeで指定される出力形式がremainingまたはremaining+lapの場合には、この時間から計測開始からの累計時間を引いたものが出力される。また、この値が正で、出力形式がsplitまたはsplit+lapの場合、累積時間に加え、この時間も出力される。 


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
    <td>minutes</td>
    <td>minute</td>
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
