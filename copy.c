/*******************************************************************************
File: IecString\copy.c
Author: Tyler Matijevich
Date: 2022-08-03
*******************************************************************************/

#include <IecString.h>
#include <stdint.h>
#include <string.h>

/* Copies source to destination up to size (of destination) or source length. Returns destination */
uint32_t IecStringCopy (char *destination, char *source, uint32_t size)
{	
	/* Declare local variables */
	const uint32_t destination_address = (uint32_t)destination;
	uint32_t bytes_remaining = size - 1;
	
	/* Verify parameters */
	if (destination == NULL || source == NULL || size == 0) return destination_address;
	
	/* Initialize if size = 1 */
	*destination = '\0';
	
	/* Copy */
	while(bytes_remaining)
	{
		if (*source == '\0')
		{
			*destination = '\0';
			break;
		}
		*destination++ = *source++;
		bytes_remaining--;
	}
	
	/* Complete with null terminator */
	*destination = '\0';
	
	return destination_address;
}
