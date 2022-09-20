/*******************************************************************************
File: IecString\copy.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include "main.h"

/* Copies source to destination up to size (of destination) or source length. Returns 0 if successful */
int32_t IecStringCopy (char *destination, uint32_t size, char *source)
{	
	/* Verify parameters */
	if (destination == NULL || source == NULL) return IECSTRING_ERROR_NULLPOINTER;
	if (size == 0) return IECSTRING_ERROR_SIZE;
	if (overlap(destination, size, source)) return IECSTRING_ERROR_OVERLAP;
	
	/* Copy, decrement first for size - 1 characters remaining */
	while (--size)
	{
		if (*source == '\0') break;
		*destination++ = *source++;
	}
	
	/* Complete with null terminator */
	*destination = '\0';
	
	if (*source == '\0') return 0;
	return IECSTRING_WARNING_TRUNCATION;
}

/* Check if destination overlaps (or will overlap) source.  Returns 0 if no overlap */
uint8_t overlap(char *destination, uint32_t size, char *source)
{
	uint32_t length = strlen(source);
	
	/* Check if destination's start overwrites source */
	if (source <= destination && destination <= source + length) return 1;
	
	/* Check if destination's end overwrites source, assumming truncation */
	if (length >= size - 1 && source - length <= destination && destination <= source) return 1;
	
	return 0;
}
