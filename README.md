# IecString

IecString is an Automation Studio library of string functions to be used with IEC 61131-1 languages such as [Structured Text](https://en.wikipedia.org/wiki/Structured_text).

The IecString library adds functionality of some C runtime libraries which are not permitted to use in Automation Studio.

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

## Functions

```C
/* Format string similar to snprintf in the C stdio library */
unsigned long IecFormatString(char *str, unsigned long size, char *format, struct FormatStringArgumentsType *args);
```

### Usage

#### IEC Structured Text 

```
// Runtime values
FormatArgs.b[0] := FALSE; // BOOL
FormatArgs.r[0] := 78.768; // LREAL
FormatArgs.i[0] := -2144327918; // DINT, e.g. Status ID
FormatArgs.s[0] := 'INIT'; // STRING
	
FormatMessage := 'Status %b, Temp %r F, Code %i, State %s';
	
MessageLength := IecFormatString(str := Message,
                                 size := SIZEOF(Message),
                                 format := FormatMessage,
                                 args := FormatArgs);
```

Message is `'Status FALSE, Temp 78.768 F, Code -2144327918, State INIT'`.

#### ANSI C 

The library and also be used with C or C++ programs.

```C
messageLength = IecFormatString(message, sizeof(message), formatMessage, &formatArgs);
```

## Automation Studio

Version 4.9.3.144 SP

### Build

You may notice build warnings such as "Additional directory/file found ..." from the IecString submodule.


Add `-W 9232 9233` to your CPU's build properties window under *Additional build options* to suppress.

## Dependencies

- `AsBrStr`

## Git

- [Install and setup Git](https://tmatijevich.github.io/gfw-tutorial/)
- [Setup gitignore for your repository](https://gist.github.com/tmatijevich/453436f1e6abc62a3d052d9b03f9db58)

## Authors

- [tmatijevich](https://github.com/tmatijevich)
