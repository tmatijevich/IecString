
FUNCTION IecFormatString : UDINT (*Format an IEC STRING with runtime date of type boolean, integer, floating point, or string. Returns formatted string length.*)
	VAR_INPUT
		str : STRING[0]; (*Destination string*)
		size : UDINT; (*Size of destination string*)
		format : STRING[0]; (*Format string*)
		args : FormatStringArgumentsType; (*Format arguments*)
	END_VAR
END_FUNCTION
