/*******************************************************************************
File: IecString\substring.c
Author: Tyler Matijevich
Date: 2022-08-10
*******************************************************************************/

#include <IecString.h>
#include <string.h>
#include <stdint.h>

/* Search source for kth occurrence of find. Use k = 0 to search last occurrence. Returns address of kth occurrence or zero if no occurrence. */
uint32_t IecStringSubstring(char *source, char *find, uint8_t k) {
	
	/* Declare local variables */
	char *src = source, *ptr = 0;
	uint32_t length;
	uint8_t i = 0;
	
	/* Verify parameters */
	if(source == NULL || find == NULL) return 0;
	
	/* Verify length */
	length = strlen(find);
	if(length > strlen(source)) return 0;
	
	/* Find */
	while(strlen(src) >= length) {
		if(memcmp(src, find, length) == 0) {
			if(i < UINT8_MAX) i++;
			else break;
			if(i == k) return (uint32_t)src;
			else ptr = src;
		}
		src++;
	}
	
	if(k == 0 && ptr != 0) return (uint32_t)ptr;
	
	return 0;
	
} /* End function */
