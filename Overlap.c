/*******************************************************************************
 * File: IecString\Overlap.c
 * Author: Tyler Matijevich
 * Date: 2022-09-20
 ******************************************************************************/

#include "Main.h"

/* Check if destination overlaps with source */
uint8_t Overlap(char *Destination, uint32_t Size, char *Source) {

	/* Local variables */
	uint32_t Length;
	
	/* Verify parameters */
	if(Destination == NULL || Source == NULL)
		return 0;
		
	/* Does destination's start overlap source's string length including null terminator */
	Length = strlen(Source);
	if(Source <= Destination && Destination <= Source + Length)
		return 1;
		
	/* Does destination's end overlap source's string length */
	if(Source <= Destination + Size - 1 && Destination + Size - 1 <= Source + Length)
		return 1;
		
	/* No overlap */
	return 0;
}
