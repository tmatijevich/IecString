(*******************************************************************************
 * File: IecString.fun
 * Author: Tyler Matijevich
 * Created: 2020-05-14
********************************************************************************)

FUNCTION IecStringCopy : UDINT (*Copies Source to Destination up to Size (of Destination) or Source length. Returns Destination*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Source : STRING[0]; (*Source string*)
		Size : UDINT; (*Size (of Destination)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringConcat : UDINT (*Concatentate Source to Destination up to Size (of Destination) or Source length. Returns Destination*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Source : STRING[0]; (*Source string*)
		Size : UDINT; (*Size (of Destination)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringReplace : UDINT (*Find in Source and replace in Destination up to Size (of Destination). Returns Destination*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Source : STRING[0]; (*Source string*)
		Find : STRING[0]; (*Find string*)
		Replace : STRING[0]; (*Replace string*)
		Size : UDINT; (*Size (of Destination)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringSubstring : UDINT (*Search Source for Kth occurence of Find. Use K = 0 to search last occurrence. Returns address of occurence or zero if no occurence.*)
	VAR_INPUT
		Source : STRING[0]; (*Source string*)
		Find : STRING[0]; (*Find string*)
		K : USINT; (*Kth occurrence*)
	END_VAR
END_FUNCTION

FUNCTION IecStringFormat : UDINT (*Format string with runtime data. Returns Destination*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string (formatted)*)
		Source : STRING[0]; (*Source string (unformatted)*)
		Args : IecStringFormatArgumentType; (*Format arguments*)
		Size : UDINT; (*Size (of Destination)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringNumber : UDINT (*Pad an integer with zeros or spaces. Returns Destination*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Number : DINT; (*Integer value*)
		Width : USINT; (*Digit width not including sign*)
		Mode : USINT; (*0 - zeros, spaces otherwise*)
		Size : UDINT; (*Size (of Destination)*)
	END_VAR
END_FUNCTION

FUNCTION IecStringToUpper : UDINT (*Convert lowercase letters to uppercase (mutable). Returns Source*)
	VAR_INPUT
		Source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringToLower : UDINT (*Convert uppercase letters to lowercase (mutable). Returns Source*)
	VAR_INPUT
		Source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION
