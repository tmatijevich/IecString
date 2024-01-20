
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
		source : STRING[0]; (*Source string*)
		find : STRING[0]; (*Search string*)
		replace : STRING[0]; (*Replace string*)
	END_VAR
END_FUNCTION

FUNCTION IecStringFormat : DINT (*Format string with runtime data*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		size : UDINT; (*Size of destination*)
		source : STRING[0]; (*Source string*)
		values : IecStringFormatType; (*Format values*)
	END_VAR
END_FUNCTION

FUNCTION IecStringDecimal : DINT (*Convert integer to string as decimal with optional padding up to width*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		size : UDINT; (*Size of destination*)
		value : DINT; (*Signed integer*)
		width : USINT; (*Minimum character width including sign*)
		flags : USINT; (*Format flags*)
	END_VAR
END_FUNCTION

FUNCTION IecStringFloat : DINT (*Convert floating point number to string*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		size : UDINT; (*Size of destination*)
		value : REAL; (*Floating point value*)
	END_VAR
END_FUNCTION

FUNCTION IecStringDateTime : DINT (*Format date and/or time*)
	VAR_INPUT
		destination : STRING[0]; (*Destination string*)
		size : UDINT; (*Size of destination*)
		format : STRING[0]; (*Format string example "yyyy-MM-dd HH:mm"*)
		date_time : DTStructure;
	END_VAR
END_FUNCTION
