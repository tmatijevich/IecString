(*******************************************************************************
 * File: IecString.typ
 * Author: Tyler Matijevich
 * Created: 2020-05-14
*******************************************************************************
 * Description: IEC type declarations
********************************************************************************)

TYPE
	FormatStringArgumentsType : 	STRUCT  (*Argument structure for runtime data to place in string*)
		b : ARRAY[0..IECSTRING_FORMATARGS_INDEX]OF BOOL; (*Place booleans TRUE or FALSE in string*)
		r : ARRAY[0..IECSTRING_FORMATARGS_INDEX]OF LREAL; (*Place floating point (casted to 32-bit) in string*)
		i : ARRAY[0..IECSTRING_FORMATARGS_INDEX]OF DINT; (*Place integer (up to 32-bit signed) in string*)
		s : ARRAY[0..IECSTRING_FORMATARGS_INDEX]OF STRING[IECSTRING_FORMATARGS_LEN]; (*Place string into string*)
	END_STRUCT;
END_TYPE
