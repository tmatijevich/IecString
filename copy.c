/*******************************************************************************
 * File: IecString\Copy.c
 * Author: Tyler Matijevich
 * Date: 2022-08-03
 ******************************************************************************/

#include "main.h"

/* Copy source to destination up to size of destination or source length */
int32_t IecStringCopy(char *Destination, uint32_t Size, char *Source) {
	
	/* Verify parameters */
	if(Destination == NULL || Source == NULL)
		return IECSTRING_ERROR_NULLPOINTER;
	if(Size == 0)
		return IECSTRING_ERROR_SIZE;
	if(Overlap(Destination, Size, Source))
		return IECSTRING_ERROR_OVERLAP;
		
	/* Copy */
	/* Decrement first, loop up to size - 1 */
	while(--Size && *Source != '\0')
		*Destination++ = *Source++;
		
	/* Null terminator */
	*Destination = '\0';
	
	/* Warn if truncated (used up size but characters from source remain) */
	return IECSTRING_WARNING_TRUNCATION * (*Source != '\0' && Size == 0);
}
