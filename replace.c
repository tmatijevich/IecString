/*******************************************************************************
 * File: IecString\Replace.c
 * Author: Tyler Matijevich
 * Date: 2022-08-03
 ******************************************************************************/

#include "main.h"

/* Find in source and replace in destination up to size of destination */
int32_t IecStringReplace(char *Destination, uint32_t Size, char *Find, char *Replace, char *Source) {
	
	/* Local variables */
	uint32_t FindLength, ReplaceLength, Offset = 0, Count;
	
	/* Verify parameters */
	if(Destination == NULL || Find == NULL || Replace == NULL || Source == NULL)
		return IECSTRING_ERROR_NULL;
	if(Size == 0)
		return IECSTRING_ERROR_SIZE;
	if(Overlap(Destination, Size, Find) || Overlap(Destination, Size, Replace) || Overlap(Destination, Size, Source))
		return IECSTRING_ERROR_OVERLAP;
		
	/* Verify length */
	FindLength = strlen(Find);
	if(FindLength > strlen(Source) || FindLength == 0)
		return IECSTRING_ERROR_LENGTH;
		
	/* Find and replace */
	ReplaceLength = strlen(Replace);
	while(Offset < Size - 1) {
		/* End of source */
		if(*Source == '\0')
			break;
			
		/* Compare */
		else if(strncmp(Source, Find, FindLength) == 0) {
			IecStringCopy(Destination, Size - Offset, Replace);
			Count = MIN(ReplaceLength, Size - Offset - 1);
			Destination += Count;
			Offset += Count;
			Source += FindLength;
		}
		
		/* Copy */
		else {
			*Destination++ = *Source++;
			Offset++;
		}	
	}
	
	/* Null terminator */
	*Destination = '\0';
	
	/* Warn if truncated (used up size but characters from source remain) */
	return IECSTRING_WARNING_TRUNCATE * (*Source != '\0' && Offset == Size - 1);
}
