# PresentationKeyDecoder

## Overview

Create slide change commands for presentation component based on input data

## Description

InPortのKeyから文字を読み込み、コンフィギュレーションで指定した文字コードに相当する文字が得られた場合に、プレゼンテーションコンポーネントのスライドページ変更コマンドに対応する数値をOutPortのSlideRelativeCommandから出力する。

### Input and Output

InPort<br/>ポート名/型/説明<br/>Key/TimedChar/入力文字。<br/>OutPort<br/>ポート名/型/説明<br/>SlideRelativeCommand/TimedShort/スライドのページを変更するためのコマンドに対応する数値。InPortのKeyへの入力文字がコンフィギュレーションのNextのいずれかに一致するときは1,Previousのいずれかに一致するときは-1,Reloadのいずれかに一致するときは0。同じ文字コードが複数のコンフィギュレーションで指定されていた場合、優先順位はNext,Previous,Reloadの順となる。

### Algorithm etc



### Basic Information

|  |  |
----|---- 
| Module Name | PresentationKeyDecoder |
| Description | Create slide change commands for presentation component based on input data |
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
      <td>InPortのKeyから文字を読み込み、コンフィギュレーションで指定した文字コードに相当する文字が得られた場合に、プレゼンテーションコンポーネントのスライドページ変更コマンドに対応する数値をOutPortのSlideRelativeCommandから出力する。</td>
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

#### Key

入力文字。

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


### OutPorts definition

#### SlideRelativeCommand

スライドのページを変更するためのコマンドに対応する数値。InPortのKeyへの入力文字がコンフィギュレーションのNextのいずれかに一致するときは1,Previousのいずれかに一致するときは-1,Reloadのいずれかに一致するときは0。同じ文字コードが複数のコンフィギュレーションで指定されていた場合、優先順位はNext,Previous,Reloadの順となる。

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


### Service Port definition


### Configuration definition

#### Next

ここに書かれた文字コードに相当する文字が入力されたときにスライドを次のページへ進めるコマンド(=1)を出力する。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">std::vector<int></td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>10,13,32,110</td>
    <td>10,13,32,110</td>
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

#### Previous

ここに書かれた文字コードに相当する文字が入力されたときにスライドを前のページへ戻すコマンド(=-1)を出力する。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">std::vector<int></td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>8,112</td>
    <td>8,112</td>
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

#### Reload

ここに書かれた文字コードに相当する文字が入力されたときにスライドの現在のページを再読み込みするコマンド(=0)を出力する。


<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">std::vector<int></td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>99,114</td>
    <td>99,114</td>
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
