/*******************************************************************************
File: IecString\concat.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include <IecString.h>
#include <string.h>
#include <stdint.h>

/* Concatentate Source to Destination up to Size (of Destination) or Source length. Returns Destination */
uint32_t IecStringConcat(char *Destination, char *Source, uint32_t Size) {
	
	/* Declare local variables */
	char *dst = Destination;
	uint32_t bytesRemaining = Size - 1, length;
	
	/* Verify parameters */
	if(Destination == NULL || Source == NULL || Size == 0) return (uint32_t)Destination;
	
	/* Current length */
	length = strlen(Destination);
	if(length >= bytesRemaining) return (uint32_t)Destination;
	
	/* Concatenate */
	dst += length;
	bytesRemaining -= length;
	IecStringCopy(dst, Source, bytesRemaining + 1);
	return (uint32_t)Destination;

} /* End function */
