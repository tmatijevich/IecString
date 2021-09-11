
FUNCTION IecFormatString : UDINT (*Format and IEC STRING with runtime arguments of type REAL, INT, or STRING*)
	VAR_INPUT
		pDestination : UDINT; (*The address of the destination string*)
		DestinationLength : UDINT; (*Size of the destination string variable, not necessarily the string length*)
		pSource : UDINT; (*The address of the source string*)
		pArguments : UDINT; (*The address of the structure holding the argument values of type FormatStringArgumentsType*)
	END_VAR
END_FUNCTION
