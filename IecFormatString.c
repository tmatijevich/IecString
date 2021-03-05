/*********************************************************************************
 * File:      IecFormatString.c
 * Author:    Tyler Matijevich
 * Created:   May 5, 2020/12:07 
 *********************************************************************************/ 

/* Must include the automatically generated header file for this library - dynamic linking */
#include <IecFrmtStr.h>
#include <stdbool.h>

static char sBool[2][6] = {"FALSE", "TRUE"}; // Two elements, five characters plus null terminator

/* Function declaration */
unsigned long IecFormatString(unsigned long pDestination, unsigned long DestinationLength, unsigned long pSource, unsigned long pArguments) {
	/*
		This function has been extracted from the Swedish BRSE_ARL library where it exists 
		solely as an internal function. Minimal changes have been made to ensure stability. 
		This function can be used with C, C++, and IEC programs.
		Date: 2020-05-01
		Created by: Unknown
		Updated by: Tyler Matijevich
	*/

	/* Create the necessary pointers, and convert from UDINTs */
	char *dst; dst = (char*)pDestination;
	char *src; src = (char*)pSource;
	FormatStringArgumentsType *args; args = (FormatStringArgumentsType*)pArguments;
	
	/* Temporary strings */
	char sFloat[13]; // optional sign, 6 significant digits (0.0001 to 999999 without scientific notation), 
					 // optional decimal, scientific notation (4) e.g. 'e+11', plus null terminator
	char sDint[12]; // -2,147,483,648 to 2,147,483647, plus null terminator
	
	/* Counters */
	unsigned short countBools = 0;
	unsigned short countFloats = 0;
	unsigned short countDints = 0;
	unsigned short countStrings = 0;
	
	unsigned long i = 0;
	unsigned char flagDestinationFull = false; // BOOL is a plcbit is a unsigned char (C)
	
	while(*src != '\0') {
		
		if(*src == '%'){
			/* Add a null character before perform concatination */
			*dst = '\0';
			
			switch(*(++src)) {
				case 'b':
					if(countBools <= FORMAT_STR_ARGS_INDEX) {
						i += brsstrlen((unsigned long)sBool[args->b[countBools]]); // Index based on boolean argument, can only be 0 or 1
						
						if(i < DestinationLength){
							brsstrcat((unsigned long)dst, (unsigned long)sBool[args->b[countBools]]);
							
							// Increment the argument index and the destination address
							dst += brsstrlen((unsigned long)sBool[args->b[countBools]]); // Update the destination before count bools
							countBools++;
							
						}
						else
							flagDestinationFull = true;
					}
					src++;
					break;
				
				case 'r':
					if(countFloats <= FORMAT_STR_ARGS_INDEX) {
						i += brsftoa(args->r[countFloats++], (unsigned long)sFloat);
						if(i < DestinationLength) {
							brsstrcat((unsigned long)dst, (unsigned long)sFloat);
							dst += brsstrlen((unsigned long)sFloat);
						}
						else
							flagDestinationFull = true;
					}
					src++; // Move on to the next character
					break;
					
				case 'i':
					if(countDints <= FORMAT_STR_ARGS_INDEX) {
						i += brsitoa((signed long)(args->i[countDints++]), (unsigned long)sDint);
						if(i < DestinationLength) {
							brsstrcat((unsigned long)dst, (unsigned long)sDint);
							dst += brsstrlen((unsigned long)sDint);
						}
						else
							flagDestinationFull = true;
					}
					src++;
					break;
					
				case 's':
					if(countStrings <= FORMAT_STR_ARGS_INDEX) {
						// Increment by the length of the string argument
						i += brsstrlen((unsigned long)(args->s[countStrings])); 
						
						// Check if it exceeds the destination length
						if(i < DestinationLength) { 
							brsstrcat((unsigned long)dst, (unsigned long)(args->s[countStrings]));
							
							// Increment the destination pointer and the string argument count
							dst += brsstrlen((unsigned long)(args->s[countStrings++])); 
						}
						else
							flagDestinationFull = true;
					}
					src++;
					break;
					
				case '%':
					if((++i) < DestinationLength) 
						*dst++ = *src++;
					else 
						flagDestinationFull = true;
				default:
					src++;
					break;
				
			} // end switch
		} 
		
		else {
			if((++i) < DestinationLength) 
				*dst++ = *src++;
			else 
				flagDestinationFull = true;
			
		} // end if
	
		
		if(flagDestinationFull) {
			break; // Break the while loop
		} // end if
		
	} // end while
	
	/* Add the null character to the end */
	*dst = '\0';
	
	return brsstrlen(pDestination);
} // end function
