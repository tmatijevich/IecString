
FUNCTION IecFormatString : UDINT (*Format a string with runtime data similiar to snprintf. Return string length.*)
	VAR_INPUT
		str : STRING[0]; (*Destination string*)
		size : UDINT; (*Size of destination string*)
		format : STRING[0]; (*Format string*)
		args : FormatStringArgumentsType; (*Format arguments*)
	END_VAR
END_FUNCTION
