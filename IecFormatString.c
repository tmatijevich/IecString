/*********************************************************************************
 * File:       IecFormatString.c
 * Date:       May 5, 2020/12:07 
 * Created by: Tyler Matijevich
 *********************************************************************************
 * Description: Perform string formatting similar to snprintf in IEC programs. The
 number of arguments is configurable but limited. This function can be used to C, 
 C++, and Structured Text programs.
 ********************************************************************************/ 

#include <IecString.h> /* Automatically generated */
#include <string.h>
#include <stdbool.h>

/* Format a string with runtime data similiar to snprintf. Return string length. */
unsigned long IecFormatString(char *str, unsigned long size, char *format, struct FormatStringArgumentsType *args) {
	
	/* Local variables */
	/* Argument strings */
	const char sBool[][6] = {"FALSE", "TRUE"}; /* Up to fize characters plus null terminator */
	/*
		LREAL
		optional sign, 6 significant digits (0.0001 to 999999 without scientific notation), 
		optional decimal, scientific notation (4) e.g. 'e+11', plus null terminator 
		
		DINT
		-2,147,483,648 to 2,147,483647, plus null terminator
	*/
	char sNum[13];
	
	/* Counters */
	unsigned char countBools 	= 0;
	unsigned char countFloats 	= 0;
	unsigned char countDints 	= 0;
	unsigned char countStrings 	= 0;
	
	/* Buffer */
	unsigned long bytesLeft = size - 1; /* Leave room for null terminator */
	unsigned long length;
	
	if(str == NULL || format == NULL || args == NULL)
		return 0;
	
	while(*format != '\0' && bytesLeft > 0) {
		
		if(*format == '%'){ /* Format specifier */
			
			*str = '\0'; /* Temporarily add null terminator to perform concatination */
			length = 0; /* Set the length to zero if the format specifier is invalid */
			
			switch(*(++format)) {
				case 'b':
					if(countBools <= FORMAT_STR_ARGS_INDEX) 
						length = strlen(strncat(str, sBool[args->b[countBools++]], bytesLeft));
					break;
				
				 case 'r':
				 	if(countFloats <= FORMAT_STR_ARGS_INDEX) {
						brsftoa((float)(args->r[countFloats++]), (unsigned long)sNum);
						length = strlen(strncat(str, sNum, bytesLeft));
				 	}
				 	break;
				 
				 case 'i':
				 	if(countDints <= FORMAT_STR_ARGS_INDEX) {
						brsitoa(args->i[countDints++], (unsigned long)sNum);
						length = strlen(strncat(str, sNum, bytesLeft));
				 	}
				 	break;
				 
				 case 's':
				 	if(countStrings <= FORMAT_STR_ARGS_INDEX) 
						length = strlen(strncat(str, args->s[countStrings++], bytesLeft));
				 	break;
				 
				 case '%':
				 	*str = '%';
					length = 1;
					break;
				
			} /* End switch */
			str += length;
			bytesLeft -= length;
			format++;
		} 
		else {
			*str++ = *format++; /* Direct copy */
			bytesLeft--;
		} /* End if format specifier */ 
		
	} /* End while */
	
	/* Add the null terminator to end the string */
	*str = '\0';
	
	return size - bytesLeft - 1;
} /* End function */
