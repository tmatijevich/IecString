/*******************************************************************************
File: IecString\Concat.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include <IecString.h>
#include <stdint.h>
#include <string.h>

/* Concatenate source to destination up to size (of destination) or source length, returns 0 if successful */
int32_t IecStringConcat(char *Destination, uint32_t Size, char *Source) {
	
	/* Local variables */
	uint32_t Length;
	
	/* Verify parameters */
	if(Destination == NULL || Source == NULL)
		return IECSTRING_ERROR_NULLPOINTER;
	if(Size == 0)
		return IECSTRING_ERROR_SIZE;
		
	/* Use string library to concatenate */
	Length = strlen(Destination);
	strncat(Destination, Source, Size - 1 - Length);
	
	/* Warn if concatenation was truncated */
	return IECSTRING_WARNING_TRUNCATION * (Length + strlen(Source) > Size - 1);
}
