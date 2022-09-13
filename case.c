/*******************************************************************************
File: IecString\case.c
Author: Tyler Matijevich
Date: 2022-08-16
*******************************************************************************/
 
#include <IecString.h>
#include <stdint.h>
#include <string.h>

/* Convert lowercase letters to uppercase (mutable). Returns source */
uint32_t IecStringToUpper (char * source)
{	
	/* Verify parameter */
	if (source == NULL) return (uint32_t)source;
	
	/* Search all of source for lowercase letters */
	while (*source != '\0')
	{
		if (IECSTRING_ASCII_LOWER_A <= *source && *source <= IECSTRING_ASCII_LOWER_Z)
		{
			/* Convert lowercase letter to uppercase */
			*source = (char)(IECSTRING_ASCII_UPPER_A + ((uint8_t)*source - IECSTRING_ASCII_LOWER_A));
		}
		source++;
	}
	
	return (uint32_t)source;
}

/* Convert uppercase letters to lowercase (mutable). Returns source */
uint32_t IecStringToLower (char * source)
{	
	/* Verify parameter */
	if (source == NULL) return (uint32_t)source;
	
	/* Search all of source for uppercase letters */
	while (*source != '\0')
	{
		if (IECSTRING_ASCII_UPPER_A <= *source && *source <= IECSTRING_ASCII_UPPER_Z)
		{
			/* Convert uppercase letter to lowercase */
			*source = (char)(IECSTRING_ASCII_LOWER_A + ((uint8_t)*source - IECSTRING_ASCII_UPPER_A));
		}
		source++;
	}
	
	return (uint32_t)source;
}
