(*******************************************************************************
 * File: IecString.fun
 * Author: Tyler Matijevich
 * Created: 2020-05-14
*******************************************************************************
 * Description: IEC function declarations
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

FUNCTION IecStringFormat : UDINT (*Format string with runtime data. Returns destination*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string (formatted)*)
		source : STRING[0]; (*Source string (unformatted)*)
		args : IecStringFormatArgumentType; (*Format arguments*)
		size : UDINT; (*Size (of destination string)*)
	END_VAR
END_FUNCTION

FUNCTION IecPadNumber : UDINT (*Pad a whole number with zeros or spaces (up to 10 digits). Return address to string.*)
	VAR_INPUT
		num : DINT; (*Signed 32-bit value*)
		str : STRING[0]; (*String reference, ensure at least 12 characters (including null terminator)*)
		digits : USINT; (*Width of digits not including sign*)
		spaces : USINT; (*0 - zeros, spaces otherwise*)
	END_VAR
END_FUNCTION
