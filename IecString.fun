
FUNCTION IecStringCopy : DINT (*Copy source to destination up to size (of destination) or source length, returns 0 if successful*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Size : UDINT; (*Size (of destination)*)
		Source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringConcat : DINT (*Concatenate source to destination up to size (of destination) or source length, returns 0 if successful*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Size : UDINT; (*Size (of destination)*)
		Source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringReplace : DINT (*Find is source and replace in destination up to size of destination*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Size : UDINT; (*Size (of destination)*)
		Find : STRING[0]; (*Search string*)
		Replace : STRING[0]; (*Replace string*)
		Source : STRING[0]; (*Source string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringFormat : DINT (*Format string with runtime data, returns 0 if successful*)
	VAR_INPUT
		Destination : STRING[0]; (*Destination string*)
		Size : UDINT; (*Size (of destination)*)
		Source : STRING[0]; (*Source string*)
		Arguments : IecStringFormatType; (*Format arguments*)
	END_VAR
END_FUNCTION
