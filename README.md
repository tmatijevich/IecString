# IecString

[![Made for B&R](https://raw.githubusercontent.com/hilch/BandR-badges/dfd5e264d7d2dd369fd37449605673f779db437d/Made-For-BrAutomation.svg)](https://www.br-automation.com)
![GitHub License](https://img.shields.io/github/license/tmatijevich/IecString)
![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/tmatijevich/IecString/total)
![GitHub issues](https://img.shields.io/github/issues-raw/tmatijevich/IecString)

IecString is an [Automation Studio](https://www.br-automation.com/en-us/products/software/automation-software/automation-studio/) library of string functions.  
The functions are intended to **enhance** string manipulation *and* **protect** memory.

**NOTE**: This is not an official library and is supported through the community.  IecString is provided as-is under the [MIT License](https://mit-license.org/) agreement.  Source code, documentation, and issues are managed through [GitHub](https://github.com/tmatijevich/IecString).

# Features

* :lock: Protect against
    * buffer overflow
    * overlapping strings
    * accessing null pointers
* :black_nib: Enhanced formatting similar to [printf](https://cplusplus.com/reference/cstdio/printf/)
* :rocket: Lightweight performance
* :white_check_mark: Compatible with ANSI C/C++ and IEC 61131-3


Function | Description
---|---
[IecStringCopy](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L2) | Copy source to destination up to size of destination or source length
[IecStringConcat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L10) | Concatenate source to destination up to size of destination or source length
[IecStringReplace](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L18) | Find in source and replace in destination
[IecStringFormat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L28) | Format string with runtime data
[IecStringDecimal](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L37) | Convert integer to string as decimal
[IecStringFloat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L47) | Convert float to string
[IecStringDateTime](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L58) | Format date and/or time

# Install

- [Download](https://github.com/tmatijevich/IecString/releases/latest/download/IecString.zip) and extract the archive.
- Import the IecString library to your project's logical view using **existing library** from the toolbox.


### Dependencies

- [AsTime](https://help.br-automation.com/#/en/4/libraries%2Fastime%2Fastime.html)

### Authors

- [tmatijevich](https://github.com/tmatijevich)
