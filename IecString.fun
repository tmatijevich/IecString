
FUNCTION IecStringCopy : DINT (*Copy source to destination up to size of destination or source length*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Size : UDINT; (*Size of destination*)
		Source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringConcat : DINT (*Concatenate source to destination up to size of destination or source length*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Size : UDINT; (*Size of destination*)
		Source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringReplace : DINT (*Find in source and replace in destination up to size of destination*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Size : UDINT; (*Size of destination*)
		Find : STRING[0]; (*Search string*)
		Replace : STRING[0]; (*Replace string*)
		Source : STRING[0]; (*Source string*)
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
