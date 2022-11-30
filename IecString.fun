
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
