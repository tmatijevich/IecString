# IecString

IecString is an Automation Studio library of string handling functions.  It is intended to supplement the AsBrStr library.

**NOTE**:  This is not an official library.  IecString is provided as-is under the GNU GPL v3.0 licence agreement.  Support for this library is provided through the [GitHub Issues List](https://github.com/tmatijevich/UserLog/issues).

## Features

- Improve memory handling with function argument for destination size
- Manipulate strings in ANSI C and IEC languages
- Support for functions from the [standard C string library](https://cplusplus.com/reference/cstring/)

## Functions

Function | Description
---|---
[IecStringCopy](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L2) | Copy source to destination up to size of destination or source length
[IecStringConcat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L10) | Concatenate source to destination up to size of destination or source length
[IecStringReplace](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L18) | Find in source and replace in destination up to size of destination
[IecStringFormat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L28) | Format string with runtime data

## Dependencies

- `AsBrStr`
