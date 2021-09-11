
FUNCTION IecFormatString : UDINT (*Format an IEC STRING with runtime date of type boolean, integer, floating point, or string. Returns formatted string length.*)
	VAR_INPUT
		pDestination : UDINT; (*Destination string*)
		DestinationLength : UDINT; (*Size of destination string*)
		pSource : UDINT; (*Format string*)
		pArguments : UDINT; (*Format arguments*)
	END_VAR
END_FUNCTION
