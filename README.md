# IecString

IecString is an Automation Studio library of string functions to be used with IEC 61131-1 languages such as [Structured Text](https://en.wikipedia.org/wiki/Structured_text).  
**NOTE:** This is not an official library. IecString is provided as is under the GNU GPL v3.0 license agreement.  
[Download the library here](https://github.com/tmatijevich/IecString/releases/latest/download/IecString.zip).  

## Clone

Clone to a reference location

```
git clone https://github.com/tmatijevich/IecString.git
```

Or, add as a submodule to your project's libraries

```
cd <project_root>
git submodule add https://github.com/tmatijevich/IecString.git <apj_root>/Logical/Libraries/IecString
```

Then add as an existing library from the Automation Studio toolbox.

# Functions

- [IecFormatString](#iecformatstring)
- [IecPadNumber](#iecpadnumber)

## [IecFormatString](https://github.com/tmatijevich/IecString/blob/main/IecFormatString.c?ts=4)

```c
/* Format a string with runtime data similiar to snprintf. Returns string length. */
unsigned long IecFormatString(char *str, unsigned long size, char *format, FormatStringArgumentsType *args);
```

### Usage

#### IEC Structured Text 

```iecst
// Runtime values
FormatArgs.b[0] := FALSE; // BOOL
FormatArgs.r[0] := 78.768; // LREAL
FormatArgs.i[0] := -2144327918; // DINT, e.g. Status ID
FormatArgs.s[0] := 'INIT'; // STRING

Format := 'Status %b, Temp %r F, Code %i, State %s';
	
Length := IecFormatString(Message, Size, Format, FormatArgs);
```

Message is `'Status FALSE, Temp 78.768 F, Code -2144327918, State INIT'`.

#### ANSI C 

IecString library is compatible with C/C++ programs.

```c
length = IecFormatString(message, sizeof(message), format, &formatArgs);
```

## [IecPadNumber](https://github.com/tmatijevich/IecString/blob/main/IecPadNumber.c?ts=4)

```c
/* Pad a whole number with zeros or spaces (up to 10 digits). Return address to string. */
unsigned long IecPadNumber(long num, char *str, unsigned char digits, unsigned char spaces);
```

### Usage

#### IEC Structured Text

```iecst
MyNumber := -1234;
Padding := 6;
Spaces := FALSE;

// Pad a number
IecPadNumber(MyNumber, Number, Padding, Spaces);
```

`Number` is a STRING and displays `-001234`.

#### ANSI C

```c
myNumber = -1234;
digits = 6;
spaces = false;

IecPadNumber(myNumber, number, digits, spaces);
```

## Build

You may notice build warnings such as "Additional directory/file found ..." from the IecString submodule.

![Build warnings project independent](https://user-images.githubusercontent.com/33841634/133009811-98cf2414-ec89-40d3-a529-34980b59e27f.png)

Add `-W 9232 9233` to your CPU's build properties window under *Additional build options* to suppress.

## Dependencies

- `AsBrStr`

## Git

- [Install and setup Git](https://tmatijevich.github.io/gfw-tutorial/)
- [Setup gitignore for your repository](https://gist.github.com/tmatijevich/453436f1e6abc62a3d052d9b03f9db58)

## Authors

- [tmatijevich](https://github.com/tmatijevich)
