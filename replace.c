/*******************************************************************************
File: IecString\replace.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include <IecString.h>
#include <string.h>
#include <stdint.h>

#define MIN(x,y) (((x) < (y)) ? (x) : (y))

/* Find in source and replace in destination up to size (of destination). Returns destination */
uint32_t IecStringReplace(char *destination, char *source, char *find, char *replace, uint32_t size) {
	
	/* Declare local variables */
	char *src = source, *dst = destination;
	uint32_t offset = 0, length, count;
	
	/* Verify parameters */
	if(destination == NULL || source == NULL || find == NULL || replace == NULL || size == 0) return (uint32_t)destination;
	
	length = strlen(find);
	if(length > strlen(source) || length == 0) {
		IecStringCopy(destination, source, size);
		return (uint32_t)destination;
	}
	
	/* Initialize (size = 1) */
	*dst = '\0';
	
	/* Find & replace */
	while(offset < size - 1) {
		if(*src == '\0') {
			*dst = '\0';
			break;
		}
		else if(memcmp(src, find, length) == 0) {
			IecStringCopy(dst, replace, size - offset);
			count = MIN(strlen(replace), size - offset - 1);
			dst += count;
			offset += count;
			src += length;
		}
		else {
			*dst++ = *src++;
			offset++;
		}
		if(offset == size - 1) *dst = '\0';
	}
	return (uint32_t)destination;
	
} /* End function */
