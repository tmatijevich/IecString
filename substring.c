/*******************************************************************************
File: IecString\substring.c
Author: Tyler Matijevich
Date: 2022-08-10
*******************************************************************************/

#include <IecString.h>
#include <string.h>
#include <stdint.h>

/* Search source for kth occurrence of find. Use k = 0 to search last occurrence. Returns address of kth occurrence or zero if no occurrence. */
uint32_t IecStringSubstring (char *source, char *find, uint8_t k)
{	
	/* Declare local variables */
	char *found = 0;
	uint32_t length;
	uint8_t i = 0;
	
	/* Verify parameters */
	if (source == NULL || find == NULL) return 0;
	
	/* Verify length */
	length = strlen(find);
	if (length > strlen(source)) return 0;
	
	/* Find */
	while (strlen(source) >= length)
	{
		if (strncmp(source, find, length) == 0)
		{
			/* If the 256th occurrence is reached, k must be zero, does not find last occurrence */
			if (i == UINT8_MAX) return 0;
			
			/* 1st through 255th occurrence */
			i++;
			if (i == k) return (uint32_t)source;
			else found = source;
		}
		source++;
	}
	
	/* Last occurrence */
	if (k == 0 && found) return (uint32_t)found;
	
	/* Nothing found */
	return 0;
}
