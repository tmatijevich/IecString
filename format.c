/*******************************************************************************
File: IecString\format.c
Author: Tyler Matijevich
Date: 2020-05-05
*******************************************************************************/

#include <IecString.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/* Format string with runtime data. Returns destination */
uint32_t IecStringFormat (char *destination, char *source, IecStringFormatArgumentType *args, uint32_t size)
{	
	/* Declare local variables */
	const uint32_t destination_address = (uint32_t)destination;
	
	/* Boolean arguments = 5 + null terminator */
	const char boolean[][6] = {"FALSE", "TRUE"}; 	
	
	/* Floats: [<+->]1.23456[e<+->12] = 12 + null terminator, Longs: -2147483648 to 2147483647 = 11 + null terminator */
	char number[13]; 
	
	uint8_t count_bool = 0;
	uint8_t count_float = 0;
	uint8_t count_integer = 0;
	uint8_t count_string = 0;
	uint32_t length, bytes_remaining = size - 1;
	
	/* Verify parameters, attempt to copy if failed */
	if (destination == NULL || source == NULL || args == NULL || size == 0) 
		return IecStringCopy(destination, source, size);
	
	/* Format */
	while (*source != '\0' && bytes_remaining > 0)
	{
		if (*source != '%')
		{
			/* Direct copy */
			*destination++ = *source++;
			bytes_remaining--;
			continue;
		}
		
		/* Temporarily add null terminator to perform concatenation */
		*destination = '\0';
		
		/* Set the length to zero if the format specifier is invalid */
		length = 0;
		
		switch (*(++source))
		{
			/* Use strncat to concatenate the formatted value up to bytes_remaining */
			/* strlen(strncat(destination, ...)) returns the length of characters appended because destination began as null */
			case 'b':
				if (count_bool <= IECSTRING_FORMAT_INDEX) 
					length = strlen(strncat(destination, boolean[args->b[count_bool++]], bytes_remaining));
				break;
			
			 case 'f':
			 	if (count_float <= IECSTRING_FORMAT_INDEX)
				{
					brsftoa((float)(args->f[count_float++]), (uint32_t)number);
					length = strlen(strncat(destination, number, bytes_remaining));
			 	}
			 	break;
			 
			 case 'i':
			 	if (count_integer <= IECSTRING_FORMAT_INDEX)
				{
					brsitoa(args->i[count_integer++], (uint32_t)number);
					length = strlen(strncat(destination, number, bytes_remaining));
			 	}
			 	break;
			 
			 case 's':
			 	if (count_string <= IECSTRING_FORMAT_INDEX) 
					length = strlen(strncat(destination, args->s[count_string++], bytes_remaining));
			 	break;
			 
			 case '%':
			 	*destination = '%';
				length = 1;
				break;
		}
		
		destination += length;
		bytes_remaining -= length;
		source++;
		
	}
	
	/* Complete with null terminator */
	*destination = '\0';
	
	return destination_address;
}
