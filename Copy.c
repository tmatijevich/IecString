/*******************************************************************************
File: IecString\Copy.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include <IecString.h>
#include <stdint.h>
#include <string.h>

/* Copy source to destination up to size (of destination) or source length, returns 0 if successful */
int32_t IecStringCopy(char *Destination, uint32_t Size, char *Source) {
	
	/* Verify parameters */
	if(Destination == NULL || Source == NULL)
		return IECSTRING_ERROR_NULLPOINTER;
	if(Size == 0)
		return IECSTRING_ERROR_SIZE;
		
	/* Copy */
	/* Decrement first, loop up to size - 1 */
	while(--Size && *Source != '\0')
		*Destination++ = *Source++;
		
	/* Complete with null terminator */
	*Destination = '\0';
	
	/* Warn if copy was truncated */
	return IECSTRING_WARNING_TRUNCATION * (*Source != '\0' && Size == 0);
}