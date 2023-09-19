# IecString [![Made for B&R](https://raw.githubusercontent.com/hilch/BandR-badges/dfd5e264d7d2dd369fd37449605673f779db437d/Made-For-BrAutomation.svg)](https://www.br-automation.com)

**IecString** is an Automation Studio library of string handling functions.  It is intended to supplement the **AsBrStr** library.

**NOTE**: This is not an official library.  IecString is provided as-is under the [GNU General Public License v3](https://www.gnu.org/licenses/gpl-3.0.txt) agreement.  Support for this library is provided through the [GitHub Issues List](https://github.com/tmatijevich/UserLog/issues).

## Features

- Improve memory handling with function argument for destination size and overlap check
- Manipulate strings in ANSI C and IEC languages
- Support for functions from the [standard C string library](https://cplusplus.com/reference/cstring/) (*coming soon*)

## Functions

Function | Description
---|---
[IecStringCopy](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L2) | Copy source to destination up to size of destination or source length
[IecStringConcat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L10) | Concatenate source to destination up to size of destination or source length
[IecStringReplace](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L18) | Find in source and replace in destination up to size of destination
[IecStringFormat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L28) | Format string with runtime data

## Dependencies

- `AsBrStr`
