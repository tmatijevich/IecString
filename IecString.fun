
FUNCTION IecStringCopy : DINT (*Copy source to destination up to size of destination or source length*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		size : UDINT; (*Size of destination*)
		source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringConcat : DINT (*Concatenate source to destination up to size of destination or source length*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		size : UDINT; (*Size of destination*)
		source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringReplace : DINT (*Find in source and replace in destination*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		size : UDINT; (*Size of destination*)
		find : STRING[0]; (*Search string*)
		replace : STRING[0]; (*Replace string*)
		source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringFormat : DINT (*Format string with runtime data*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Size : UDINT; (*Size of destination*)
		Source : STRING[0]; (*Source string*)
		Values : IecStringFormatType; (*Format values*)
	END_VAR
END_FUNCTION
