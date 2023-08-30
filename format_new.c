/*******************************************************************************
 * File: IecString\Format.c
 * Author: Tyler Matijevich
 * Date: 2020-05-05
 ******************************************************************************/

#include "main_new.h"

/* Format string with runtime data */
int32_t IecStringFormat(char *Destination, uint32_t Size, char *Source, IecStringFormatType *Values) {
	
	/* Local variables */
	/* Boolean arguments: 5 characters + null terminator */
	const char Boolean[][6] = {"FALSE", "TRUE"};
	
	/* Floats: [<+->]1.23456[e<+->12] = 12 characters + null terminator */
	/* Longs: -2147483648 to 2147483647 = 11 characters + null terminator */
	char Number[13];
	
	/* Counters */
	uint8_t CountBool = 0, CountFloat = 0, CountInteger = 0, CountString = 0;
	uint32_t Length, BytesRemaining = Size - 1;
	
	/* Verify parameters */
	if(Destination == NULL || Source == NULL || Values == NULL)
		return IECSTRING_ERROR_NULLPOINTER;
	if(Size == 0)
		return IECSTRING_ERROR_SIZE;
	if(Overlap(Destination, Size, Source))
		return IECSTRING_ERROR_OVERLAP;
		
	/* Format */
	while(*Source != '\0' && BytesRemaining) {
		
		/* Check for specifier, copy otherwise */
		if(*Source != '%') {
			*Destination++ = *Source++;
			BytesRemaining--;
			continue;
		}
		
		/* Temporarily add null terminator to perform concatenation */
		*Destination = '\0';
		
		/* Reset length */
		Length = 0;
		
		switch(*(++Source)) {
			case 'b':
				if(CountBool <= IECSTRING_FORMAT_INDEX)
					Length = strlen(strncat(Destination, Boolean[Values->b[CountBool++]], BytesRemaining));
				break;
				
			case 'f':
				if(CountFloat <= IECSTRING_FORMAT_INDEX) {
					brsftoa((float)Values->f[CountFloat++], (uint32_t)Number);
					Length = strlen(strncat(Destination, Number, BytesRemaining));
				}
				break;
				
			case 'i':
				if(CountInteger <= IECSTRING_FORMAT_INDEX) {
					brsitoa(Values->i[CountInteger++], (uint32_t)Number);
					Length = strlen(strncat(Destination, Number, BytesRemaining));
				}
				break;
				
			case 's':
				if(CountString <= IECSTRING_FORMAT_INDEX) 
					Length = strlen(strncat(Destination, Values->s[CountString++], BytesRemaining));
				break;
				
			case '%':
				*Destination = '%';
				Length = 1;
				break;
		}
		
		Destination += Length;
		BytesRemaining -= Length;
		Source++;
	}
	
	/* Null terminator */
	*Destination = '\0';
	
	/* Warn if truncated (used up size but characters from source remain) */
	return IECSTRING_WARNING_TRUNCATION * (*Source != '\0' && BytesRemaining == 0);
}
