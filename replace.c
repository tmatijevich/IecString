/*******************************************************************************
File: IecString\replace.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include <IecString.h>
#include <string.h>
#include <stdint.h>

#define MIN(x,y) (((x) < (y)) ? (x) : (y))

/* Find in Source and replace in Destination up to Size (of Destination). Returns Destination */
uint32_t IecStringReplace(char *Destination, char *Source, char *Find, char *Replace, uint32_t Size) {
	
	/* Declare local variables */
	char *src = Source, *dst = Destination;
	uint32_t offset = 0, length, count;
	
	/* Verify parameters */
	if(Destination == NULL || Source == NULL || Find == NULL || Replace == NULL || Size == 0) return (uint32_t)Destination;
	
	length = strlen(Find);
	if(length > strlen(Source) || length == 0) {
		IecStringCopy(Destination, Source, Size);
		return (uint32_t)Destination;
	}
	
	/* Initialize (Size = 1) */
	*dst = '\0';
	
	/* Find & Replace */
	while(offset < Size - 1) {
		if(*src == '\0') {
			*dst = '\0';
			break;
		}
		else if(memcmp(src, Find, length) == 0) {
			IecStringCopy(dst, Replace, Size - offset);
			count = MIN(strlen(Replace), Size - offset - 1);
			dst += count;
			offset += count;
			src += length;
		}
		else {
			*dst++ = *src++;
			offset++;
		}
		if(offset == Size - 1) *dst = '\0';
	}
	return (uint32_t)Destination;
	
} /* End function */
