/*******************************************************************************
File: IecString\copy.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include <IecString.h>
#include <stdint.h>
#include <string.h>

/* Copies Source to Destination up to Size (of Destination) or Source length. Returns Destination */
uint32_t IecStringCopy(char *Destination, char *Source, uint32_t Size) {
	
	/* Declare local variables */
	char *src = Source, *dst = Destination;
	uint32_t bytesRemaining = Size - 1;
	
	/* Verify parameters */
	if(Destination == NULL || Source == NULL || Size == 0) return (uint32_t)Destination;
	
	/* Initialize (Size = 1) */
	*dst = '\0';
	
	/* Copy */
	while(bytesRemaining) {
		if(*src == '\0') {
			*dst = '\0';
			break;
		}
		*dst++ = *src++;
		bytesRemaining--;
		if(bytesRemaining == 0) *dst = '\0';
	}
	
	return (uint32_t)Destination;
	
} /* End function */
