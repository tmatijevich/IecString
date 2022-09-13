(*******************************************************************************
 * File: IecString.fun
 * Author: Tyler Matijevich
 * Created: 2020-05-14
********************************************************************************)

FUNCTION IecStringCopy : UDINT (*Copies source to destination up to size (of destination) or source length. Returns destination*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		source : STRING[0]; (*Source string*)
		size : UDINT; (*Size (of destination)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringConcat : UDINT (*Concatentate source to destination up to size (of destination) or source length. Returns destination*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		source : STRING[0]; (*Source string*)
		size : UDINT; (*Size (of destination)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringReplace : UDINT (*Find in source and replace in destination up to size (of destination). Returns destination*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		source : STRING[0]; (*Source string*)
		find : STRING[0]; (*Find string*)
		replace : STRING[0]; (*Replace string*)
		size : UDINT; (*Size (of destination)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringSubstring : UDINT (*Search source for kth occurrence of find. Use k = 0 to search last occurrence. Returns address of kth occurrence or zero if no occurrence.*)
	VAR_INPUT
		source : STRING[0]; (*Source string*)
		find : STRING[0]; (*Find string*)
		k : USINT; (*kth occurrence*)
	END_VAR
END_FUNCTION

FUNCTION IecStringFormat : UDINT (*Format string with runtime data. Returns destination*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string (formatted)*)
		source : STRING[0]; (*Source string (unformatted)*)
		args : IecStringFormatArgumentType; (*Format arguments*)
		size : UDINT; (*Size (of destination string)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringNumber : UDINT (*Pad an integer with zeros or spaces. Returns destination*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		number : DINT; (*Integer value*)
		width : USINT; (*Digit width not including sign*)
		mode : USINT; (*0 - zeros, spaces otherwise*)
		size : UDINT; (*Size (of destination)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringToUpper : UDINT (*Convert lowercase letters to uppercase (mutable). Returns source*)
	VAR_INPUT
		source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringToLower : UDINT (*Convert uppercase letters to lowercase (mutable). Returns source*)
	VAR_INPUT
		source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION
