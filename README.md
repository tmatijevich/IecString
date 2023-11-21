# IecString [![Made for B&R](https://raw.githubusercontent.com/hilch/BandR-badges/dfd5e264d7d2dd369fd37449605673f779db437d/Made-For-BrAutomation.svg)](https://www.br-automation.com)

IecString is an [Automation Studio](https://www.br-automation.com/en-us/products/software/automation-software/automation-studio/) library of string handling functions.  It is intended to supplement the AsBrStr library for [IEC 61131-3](https://en.wikipedia.org/wiki/IEC_61131-3) programming languages.

![2023-11-21_12 20 40](https://github.com/tmatijevich/IecString/assets/33841634/ed94dafc-efe3-4987-a1ce-e3303e3056d8)

**NOTE**: This is not an official library and is supported through the community.  IecString is provided as-is under the [MIT License](https://mit-license.org/) agreement.  Source code, documentation, and issues are managed through [GitHub](https://github.com/tmatijevich/IecString).

## Install

- [Download](https://github.com/tmatijevich/IecString/releases/latest/download/IecString.zip) and extract the archive.
- Import the IecString package to your Automation Studio's Logical View using **Existing Library** from the toolbox.

## Features

- Improve memory safety with:
    - Destination size check
    - Overlap check
- Format strings in ANSI C and IEC languages

## Functions

Function | Description
---|---
[IecStringCopy](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L2) | Copy source to destination up to size of destination or source length
[IecStringConcat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L10) | Concatenate source to destination up to size of destination or source length
[IecStringReplace](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L18) | Find in source and replace in destination up to size of destination
[IecStringFormat](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L28) | Format string with runtime data
[IecStringInteger](https://github.com/tmatijevich/IecString/blob/main/IecString.fun#L37) | Pad a whole number with zeros or spaces

## Build

Clone to a reference location.

```bash
git clone https://github.com/tmatijevich/IecString.git
```

Or, add as a submodule to a project's libraries.

```bash
cd <project_root>
git submodule add https://github.com/tmatijevich/IecString.git <project_root>/Logical/Libraries/IecString
```

### Warnings

![161134955-5e71050f-bd1b-49cf-b07c-6408ae3c24ca](https://github.com/tmatijevich/IecString/assets/33841634/f95acd25-1841-4b30-a3a4-283497dc3120)

In Automation Studio 4.11+,

1. Configuration View
2. Right-click the CPU object and select Properties
3. Navigate to the Build tab
4. Add the following to the **Objects ignored for build warnings 9232 and 9233** field

```
*README*;*LICENSE*;.git;.gitignore;.github
```

Prior to Automation Studio 4.11,

1. Configuration View
2. Right-click the CPU object and select Properties
3. Navigate to the Build tab
4. Add the following to the **Additional build options** field

```
-W 9232 9233
```

## Dependencies

- AsBrStr

## Authors

- [tmatijevich](https://github.com/tmatijevich)
