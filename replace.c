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
uint32_t IecStringReplace (char *destination, char *source, char *find, char *replace, uint32_t size)
{
	/* Declare local variables */
	const uint32_t destination_address = (uint32_t)destination;
	uint32_t offset = 0, length, count;
	
	/* Verify parameters, attempt to copy if failed */
	if (destination == NULL || source == NULL || find == NULL || replace == NULL || size == 0) 
		return IecStringCopy(destination, source, size);
	
	/* Verify length, attempt to copy if failed */
	length = strlen(find);
	if (length > strlen(source) || length == 0)
		return IecStringCopy(destination, source, size);
	
	/* Find & replace */
	while (offset < size - 1)
	{
		/* End of search */
		if (*source == '\0') break;
		
		/* Compare up to strlen(find) characters */
		else if (strncmp(source, find, length) == 0)
		{
			/* Copy replace to current destination pointer with remaining bytes */
			IecStringCopy(destination, replace, size - offset);
			
			/* Determine how many bytes were copied and update destination and offset */
			count = MIN(strlen(replace), size - offset - 1);
			destination += count;
			offset += count;
			
			/* Update source from strlen(find) */
			source += length;
		}
		
		/* Direct copy of source to destination */
		else
		{
			*destination++ = *source++;
			offset++;
		}
	}
	
	/* Complete with null terminator */
	*destination = '\0';
	
	return destination_address;	
}
