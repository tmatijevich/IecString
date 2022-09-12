(*******************************************************************************
 * File: IecString.typ
 * Author: Tyler Matijevich
 * Created: 2020-05-14
********************************************************************************)

TYPE
	IecStringFormatArgumentType : 	STRUCT  (*Argument structure for runtime data*)
		b : ARRAY[0..IECSTRING_FORMAT_INDEX]OF BOOL; (*Place boolean (TRUE or FALSE)*)
		f : ARRAY[0..IECSTRING_FORMAT_INDEX]OF LREAL; (*Place floating point (double casted float)*)
		i : ARRAY[0..IECSTRING_FORMAT_INDEX]OF DINT; (*Place integer (32-bit signed)*)
		s : ARRAY[0..IECSTRING_FORMAT_INDEX]OF STRING[IECSTRING_FORMAT_LENGTH]; (*Place string*)
	END_STRUCT;
END_TYPE
