/*******************************************************************************
File: IecString\case.c
Author: Tyler Matijevich
Date: 2022-08-16
*******************************************************************************/
 
#include <IecString.h>
#include <stdint.h>
#include <string.h>

/* Convert lowercase letters to uppercase (mutable). Returns source */
uint32_t IecStringToUpper(char *source) {
	
	char *src = source;
	
	if(source == NULL) return (uint32_t)source;
	
	while(*src != '\0') {
		if(IECSTRING_ASCII_LOWER_A <= *src && *src <= IECSTRING_ASCII_LOWER_Z) {
			*src = (char)(IECSTRING_ASCII_UPPER_A + ((uint8_t)*src - IECSTRING_ASCII_LOWER_A));
		}
		src++;
	}
	
	return (uint32_t)source;
	
} /* End function */

/* Convert uppercase letters to lowercase (mutable). Returns source */
uint32_t IecStringToLower(char *source) {
	
	char *src = source;
	
	if(source == NULL) return (uint32_t)source;
	
	while(*src != '\0') {
		if(IECSTRING_ASCII_UPPER_A <= *src && *src <= IECSTRING_ASCII_UPPER_Z) {
			*src = (char)(IECSTRING_ASCII_LOWER_A + ((uint8_t)*src - IECSTRING_ASCII_UPPER_A));
		}
		src++;
	}
	
	return (uint32_t)source;
	
} /* End function */