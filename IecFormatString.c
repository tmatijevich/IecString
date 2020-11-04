/* Must include the automatically generated header file for this library - dynamic linking */
#include "IecFrmtStr.h"

/* Function declaration */
//void fnFormatString(char* dst, char* src, FormatStringArguments_typ* pArgs) { - does not match the declaration datatypes
unsigned long IecFormatString(unsigned long pDestination, unsigned long destinationLength, unsigned long pSource, unsigned long pArguments) {
	/*
		This function has been extracted from the BRSE_ARL library where it exists solely 
		as an internal function. Minimal changes have been made to ensure stability. This 
		function can be used with C, C++, and IEC programs.
		Date: 2020-05-01
		Created by: Unknown
		Updated by: Tyler Matijevich
	*/

	/* Create the necessary pointers, and convert from UDINTs */
	char *dst; dst = (char*)pDestination;
	char *src; src = (char*)pSource;
	FormatStringArgumentsType *args; args = (FormatStringArgumentsType*)pArguments;
	
	/* Temporary strings */
	char sFloat[13]; // sign, 6 significant digits (or 0.0001...), one decimal, scientific notation e.g. 'e+010'
	// Scientific notation starts at 1e+006 or 1e-005
	char sInt[6];
	
	/* Counters */
	unsigned short countFloats = 0;
	unsigned short countInts = 0;
	unsigned short countStrings = 0;
	
	unsigned long i = 0;
	char flagDestinationFull = 0;
	
	while(*src != '\0') {
		
		if(*src == '%'){
			/* Add a null character before perform concatination */
			*dst = '\0';
			
			switch(*(++src)) {
				case 'r':
					if(countFloats <= FORMAT_STR_MAX_INDEX_ARGS) {
						i += brsftoa(args->r[countFloats++], (unsigned long)sFloat);
						if(i < destinationLength) {
							brsstrcat((unsigned long)dst, (unsigned long)sFloat);
							dst += brsstrlen((unsigned long)sFloat);
						}
						else
							flagDestinationFull = 1;
					}
					src++; // Move on to the next character
					break;
					
				case 'i':
					if(countInts <= FORMAT_STR_MAX_INDEX_ARGS) {
						i += brsitoa((signed long)(args->i[countInts++]), (unsigned long)sInt);
						if(i < destinationLength) {
							brsstrcat((unsigned long)dst, (unsigned long)sInt);
							dst += brsstrlen((unsigned long)sInt);
						}
						else
							flagDestinationFull = 1;
					}
					src++;
					break;
					
				case 's':
					if(countStrings <= FORMAT_STR_MAX_INDEX_ARGS) {
						// Increment by the length of the string argument
						i += brsstrlen((unsigned long)(args->s[countStrings])); 
						
						// Check if it exceeds the destination length
						if(i < destinationLength) { 
							brsstrcat((unsigned long)dst, (unsigned long)(args->s[countStrings]));
							
							// Increment the destination pointer and the string argument count
							dst += brsstrlen((unsigned long)(args->s[countStrings++])); 
						}
						else
							flagDestinationFull = 1;
					}
					src++;
					break;
					
				case '%':
					if((++i) < destinationLength) 
						*dst++ = *src++;
					else 
						flagDestinationFull = 1;
				default:
					src++;
					break;
				
			} // end switch
		} 
		
		else {
			if((++i) < destinationLength) 
				*dst++ = *src++;
			else 
				flagDestinationFull = 1;
			
		} // end if
	
		
		if(flagDestinationFull) {
			break; // Break the while loop
		} // end if
		
	} // end while
	
	/* Add the null character to the end */
	*dst = '\0';
	
	return brsstrlen(pDestination);
} // end function
