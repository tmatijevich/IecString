/*********************************************************************************
 * File:        IecFormatString.c
 * Date:        May 5, 2020/12:07 
 * Created by:  Tyler Matijevich
 *********************************************************************************
 * Description: Perform string formatting in IEC programs similar to snprintf. The
 number of arguments is configurable but limited. This function can be used in C, 
 C++, and IEC programs.
 ********************************************************************************/ 

#include <IecString.h> /* Automatically generated */
#include <string.h>
#include <stdbool.h>

/* Format a string with runtime data similiar to snprintf. Returns string length. */
unsigned long IecFormatString(char *str, unsigned long size, char *format, FormatStringArgumentsType *args) {
	
	/* Local variables */
	const char sBool[][6] = {"FALSE", "TRUE"}; 	/* Boolean arguments = 5 + null terminator */
	char sNum[13]; 								/* Floats: [<+->]1.23456[e<+->12] = 12 + null terminator, Longs: -2147483648 to 2147483647 = 11 + null terminator */
	unsigned char countBools = 0;
	unsigned char countFloats = 0;
	unsigned char countLongs = 0;
	unsigned char countStrings = 0; 
	unsigned long length, bytesLeft = size - 1; /* Guard output, leave room for null terminator */
	
	/* Guard null pointers */
	if(str == NULL || format == NULL || args == NULL) 
		return 0;
	
	while(*format != '\0' && bytesLeft > 0) {
		if(*format != '%') {
			*str++ = *format++; /* Direct copy */
			bytesLeft--;
			continue;
		}
		
		*str = '\0'; /* Temporarily add null terminator to perform concatination */
		length = 0; /* Set the length to zero if the format specifier is invalid */
		
		switch(*(++format)) {
			case 'b':
				if(countBools <= IECSTRING_FORMATARGS_INDEX) 
					length = strlen(strncat(str, sBool[args->b[countBools++]], bytesLeft));
				break;
			
			 case 'r':
			 	if(countFloats <= IECSTRING_FORMATARGS_INDEX) {
					brsftoa((float)(args->r[countFloats++]), (unsigned long)sNum);
					length = strlen(strncat(str, sNum, bytesLeft));
			 	}
			 	break;
			 
			 case 'i':
			 	if(countLongs <= IECSTRING_FORMATARGS_INDEX) {
					brsitoa(args->i[countLongs++], (unsigned long)sNum);
					length = strlen(strncat(str, sNum, bytesLeft));
			 	}
			 	break;
			 
			 case 's':
			 	if(countStrings <= IECSTRING_FORMATARGS_INDEX) 
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
		
	} /* End while */
	
	*str = '\0'; /* Add the null terminator to end the string */
	return size - bytesLeft - 1;
	
} /* End function */
