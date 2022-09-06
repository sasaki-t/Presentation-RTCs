# ConsoleInString

## Overview

Console string input component

## Description

コンソールから入力された文字列をOutPortのStringから出力する。<br/>アクティブ状態ではコンソールからの入力待ちをしているので、非アクティブ化する場合は非アクティブ化の指示をした後、コンソールから何か文字列を入力する必要がある。

### Input and Output

OutPort<br/>ポート名/型/説明<br/>String/TimedString/コンソールから入力された文字列。

### Algorithm etc



### Basic Information

|  |  |
----|---- 
| Module Name | ConsoleInString |
| Description | Console string input component |
| Version | 1.1.0 |
| Vendor | TakeshiSasaki |
| Category | example |
| Comp. Type | COMMUTATIVE |
| Act. Type | SPORADIC |
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
    <td>on_activated</td>
    <td colspan="2"></td>
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
      <td>コンソールから入力された文字列をOutPortのStringから出力する。</td>
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


### OutPorts definition

#### String

コンソールから入力された文字列。

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


### Service Port definition


### Configuration definition


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
