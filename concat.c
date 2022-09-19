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
	/* Verify parameters */
	if (destination == NULL || source == NULL || size == 0) return (uint32_t)destination;
	
	/* Use cstring */
	return (uint32_t)strncat(destination, source, size - 1);
}
