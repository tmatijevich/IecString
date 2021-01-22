
TYPE
	FormatStringArgumentsType : 	STRUCT  (*Argument structure for gathering runtime data to place into the formatted string*)
		b : ARRAY[0..FORMAT_STR_ARGS_INDEX]OF BOOL; (*BOOL variables to place TRUE of FALSE into the formatted string*)
		r : ARRAY[0..FORMAT_STR_ARGS_INDEX]OF REAL; (*REAL variables to place inside the formatted string, similar to %f*)
		i : ARRAY[0..FORMAT_STR_ARGS_INDEX]OF DINT; (*DINT variables to place inside the formatted string, similar to %d*)
		s : ARRAY[0..FORMAT_STR_ARGS_INDEX]OF STRING[FORMAT_STR_ARGS_LEN]; (*STRING variable to place inside the formatted string, similar to %s*)
	END_STRUCT;
END_TYPE
