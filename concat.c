/*******************************************************************************
File: IecString\concat.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include <IecString.h>
#include <string.h>
#include <stdint.h>

/* Concatentate source to destination up to size (of destination) or source length. Returns destination */
uint32_t IecStringConcat(char *destination, char *source, uint32_t size) {
	
	/* Declare local variables */
	char *dst = destination;
	uint32_t bytesRemaining = size - 1, length;
	
	length = strlen(destination);
	if(length >= bytesRemaining) return (uint32_t)destination;
	
	dst += length;
	bytesRemaining -= length;
	IecStringCopy(dst, source, bytesRemaining + 1);
	return (uint32_t)destination;

} /* End function */
