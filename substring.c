/*******************************************************************************
File: IecString\substring.c
Author: Tyler Matijevich
Date: 2022-08-10
*******************************************************************************/

#include <IecString.h>
#include <string.h>
#include <stdint.h>

/* Search Source for Kth occurence of Find. Use K = 0 to search last occurrence. Returns address of occurence or zero if no occurence. */
uint32_t IecStringSubstring(char *Source, char *Find, uint8_t K) {
	
	/* Declare local variables */
	char *src = Source, *ptr = 0;
	uint32_t length;
	uint8_t i = 0;
	
	/* Verify parameters */
	if(Source == NULL || Find == NULL) return 0;
	
	/* Verify length */
	length = strlen(Find);
	if(length > strlen(Source)) return 0;
	
	/* Find */
	while(strlen(src) >= length) {
		if(memcmp(src, Find, length) == 0) {
			if(i < UINT8_MAX) i++;
			else break;
			if(i == K) return (uint32_t)src;
			else ptr = src;
		}
		src++;
	}
	
	if(K == 0 && ptr != 0) return (uint32_t)ptr;
	
	return 0;
	
} /* End function */
