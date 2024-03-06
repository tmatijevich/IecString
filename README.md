# IecString

[![Made for B&R](https://raw.githubusercontent.com/hilch/BandR-badges/dfd5e264d7d2dd369fd37449605673f779db437d/Made-For-BrAutomation.svg)](https://www.br-automation.com)
[![GitHub License](https://img.shields.io/github/license/tmatijevich/IecString)](https://github.com/tmatijevich/IecString?tab=MIT-1-ov-file#MIT-1-ov-file)
[![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/tmatijevich/IecString/total)](https://github.com/tmatijevich/IecString/releases/latest/download/IecString.zip)
[![GitHub issues](https://img.shields.io/github/issues-raw/tmatijevich/IecString)](https://github.com/tmatijevich/IecString/issues)

IecString is an [Automation Studio](https://www.br-automation.com/en-us/products/software/automation-software/automation-studio/) library of string functions.  
The functions **enhance** string manipulation, **protect** memory, and support ANSI C/C++ and [IEC 61131-3](https://en.wikipedia.org/wiki/IEC_61131-3).

**NOTE**: This is not an official library and is supported through the community.  IecString is provided as-is under the [MIT License](https://mit-license.org/) agreement.  Source code, documentation, and issues are managed through [GitHub](https://github.com/tmatijevich/IecString).

# Features

* :lock: Protect against
    * buffer overflow
    * overlapping strings
    * accessing null pointers
* :black_nib: Enhanced formatting similar to [printf](https://cplusplus.com/reference/cstdio/printf/)
* :rocket: Lightweight performance
* :white_check_mark: Compatible with ANSI C/C++ and IEC 61131-3


Function | Read | Write | Description
---|---|---|---
[IecStringCopy](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L2) | :mag: | :memo: | Copy source to destination up to size of destination or source length
[IecStringConcat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L10) | :mag: | :memo: | Concatenate source to destination up to size of destination or source length
[IecStringReplace](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L18) | :mag: | :memo: | Find in source and replace in destination
[IecStringFormat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L28) | :mag: | :memo: | Format string with runtime data
[IecStringDecimal](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L37) | | :memo: | Convert integer to string as decimal
[IecStringFloat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L47) | | :memo: | Convert float to string
[IecStringDateTime](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L58) | :mag: | :memo: | Format date and/or time

# Install

- [Download](https://github.com/tmatijevich/IecString/releases/latest/download/IecString.zip) the binaries and extract the archive
- Add to the project as **existing library** from the toolbox in logical view

# Build

- Clone or download source files
- Add to the project as **existing library**
    - Option to add as **reference**

Alternatively, add as submodule to an existing project repository.

```
cd <repository>
git submodule add https://github.com/tmatijevich/IecString.git <project>/Logical/Libraries/IecString
```

Then add to project as **existing library**.

# Performance & Unit Tests

See the [IecStringProject](https://github.com/tmatijevich/IecStringProject) for all function unit tests and hardware performance tests.

# Documentation

Once installed, the help file can be view using the `F1` function key.

See the [IecStringHelp](https://github.com/tmatijevich/IecStringHelp).  This help is included in the binary download of this library.

### Dependencies

- [AsTime](https://help.br-automation.com/#/en/4/libraries%2Fastime%2Fastime.html)

### Authors

- Tyler Matijevich ([@tmatijevich](https://github.com/tmatijevich))
