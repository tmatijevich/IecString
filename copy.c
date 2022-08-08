/*******************************************************************************
File: IecString\copy.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include <IecString.h>
#include <stdint.h>

/* Copies source to destination up to size (of destination) or source length. Returns destination */
uint32_t IecStringCopy(char *destination, char *source, uint32_t size) {
	
	/* Declare local variables */
	char *src = source, *dst = destination;
	uint32_t bytesRemaining = size - 1;
	
	while(bytesRemaining) {
		if(*src == '\0') {
			*dst = '\0';
			break;
		}
		*dst++ = *src++;
		bytesRemaining--;
		if(bytesRemaining == 0) *dst = '\0';
	}
	
	return (uint32_t)destination;
	
} /* End function */
