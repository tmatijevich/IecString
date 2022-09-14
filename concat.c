/*******************************************************************************
File: IecString\concat.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include <IecString.h>
#include <string.h>
#include <stdint.h>

/* Concatentate source to destination up to size (of destination) or source length. Returns destination */
uint32_t IecStringConcat (char *destination, char *source, uint32_t size)
{	
	/* Declare local variables */
	const uint32_t destination_address = (uint32_t)destination;
	uint32_t bytes_remaining = size - 1, length;
	
	/* Verify parameters */
	if (destination == NULL || source == NULL || size == 0) return destination_address;
	
	/* Current length */
	length = strlen(destination);
	if (length >= bytes_remaining) return destination_address;
	
	/* Concatenate */
	destination += length;
	bytes_remaining -= length;
	IecStringCopy(destination, source, bytes_remaining + 1);
	
	return destination_address;
}
