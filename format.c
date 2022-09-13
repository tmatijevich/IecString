/*******************************************************************************
File: IecString\format.c
Author: Tyler Matijevich
Date: 2020-05-05
*******************************************************************************/

#include <IecString.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/* Format string with runtime data. Returns destination */
uint32_t IecStringFormat(char *destination, char *source, IecStringFormatArgumentType *args, uint32_t size) {
	
	/* Declare local variables */
	char *src = source, *dst = destination;
	const char sBool[][6] = {"FALSE", "TRUE"}; 	/* Boolean arguments = 5 + null terminator */
	char sNumber[13]; /* Floats: [<+->]1.23456[e<+->12] = 12 + null terminator, Longs: -2147483648 to 2147483647 = 11 + null terminator */
	uint8_t countBool = 0;
	uint8_t countFloat = 0;
	uint8_t countInteger = 0;
	uint8_t countString = 0; 
	uint32_t length, bytesRemaining = size - 1;
	
	/* Verify parameters */
	if(destination == NULL || source == NULL || size == 0) return (uint32_t)destination;
	if(args == NULL) return IecStringCopy(destination, source, size);
	
	/* Format */
	while(*src != '\0' && bytesRemaining > 0) {
		if(*src != '%') {
			*dst++ = *src++; /* Direct copy */
			bytesRemaining--;
			continue;
		}
		
		*dst = '\0'; /* Temporarily add null terminator to perform concatenation */
		length = 0; /* Set the length to zero if the format specifier is invalid */
		
		switch(*(++src)) {
			case 'b':
				if(countBool <= IECSTRING_FORMAT_INDEX) 
					length = strlen(strncat(dst, sBool[args->b[countBool++]], bytesRemaining));
				break;
			
			 case 'f':
			 	if(countFloat <= IECSTRING_FORMAT_INDEX) {
					brsftoa((float)(args->f[countFloat++]), (uint32_t)sNumber);
					length = strlen(strncat(dst, sNumber, bytesRemaining));
			 	}
			 	break;
			 
			 case 'i':
			 	if(countInteger <= IECSTRING_FORMAT_INDEX) {
					brsitoa(args->i[countInteger++], (uint32_t)sNumber);
					length = strlen(strncat(dst, sNumber, bytesRemaining));
			 	}
			 	break;
			 
			 case 's':
			 	if(countString <= IECSTRING_FORMAT_INDEX) 
					length = strlen(strncat(dst, args->s[countString++], bytesRemaining));
			 	break;
			 
			 case '%':
			 	*dst = '%';
				length = 1;
				break;
		} /* End switch */
		
		dst += length;
		bytesRemaining -= length;
		src++;
		
	} /* End while */
	
	*dst = '\0'; /* Add the null terminator to end the string */
	return (uint32_t)destination;
	
} /* End function */
