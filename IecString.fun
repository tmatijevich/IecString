(*******************************************************************************
 * File: IecString.fun
 * Author: Tyler Matijevich
 * Created: 2020-05-14
********************************************************************************)

FUNCTION IecStringCopy : UDINT (*Copies source to destination up to size (of destination) or source length. Returns destination*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		source : STRING[0]; (*Source string*)
		size : UDINT; (*Size (of destination string)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringConcat : UDINT (*Concatentate source to destination up to size (of destination) or source length. Returns destination*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		source : STRING[0]; (*Source string*)
		size : UDINT; (*Size (of destination string)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringReplace : UDINT (*Find in source and replace in destination up to size (of destination). Returns destination*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		source : STRING[0]; (*Source string*)
		find : STRING[0]; (*Find string*)
		replace : STRING[0]; (*Replace string*)
		size : UDINT; (*Size (of destination string)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringSubstring : UDINT (*Search source for first occurence of find. Returns address of first occurence or zero if no occurence.*)
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
		size : UDINT; (*Size (of destination string)*)
	END_VAR
END_FUNCTION
