(*******************************************************************************
 * File: IecString.fun
 * Author: Tyler Matijevich
 * Created: 2020-05-14
*******************************************************************************
 * Description: IEC function declarations
********************************************************************************)

FUNCTION IecStringCopy : UDINT (*Copies source to destination up to size (of destination) or source length. Returns source*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		source : STRING[0]; (*Source string*)
		size : UDINT; (*Size (of destination string)*)
	END_VAR
END_FUNCTION

FUNCTION IecFormatString : UDINT (*Format a string with runtime data similiar to snprintf. Return string length.*)
	VAR_INPUT
		str : STRING[0]; (*Destination string*)
		size : UDINT; (*Size of destination string*)
		format : STRING[0]; (*Format string*)
		args : FormatStringArgumentsType; (*Format arguments*)
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
