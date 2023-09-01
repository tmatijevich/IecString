/*******************************************************************************
 * File: overlap.c
 * Created: 2022-09-20
 * 
 * Contributors: 
 * - Tyler Matijevich
 * 
 * License:
 *  This file overlap.c is part of the IecString project released under the
 *  GNU General Public License v3.0 agreement.  For more information, please 
 *  visit https://github.com/tmatijevich/IecString/blob/main/LICENSE.
 ******************************************************************************/

#include "main.h"

/* Check if destination overlaps with source */
uint8_t Overlap(char *destination, uint32_t size, char *source) {

    /* Local variables */
    char *end;
    uint8_t overlap;
    uint32_t length;
    
    /* Verify parameters */
    if (destination == NULL || source == NULL)
        return false;
        
    length = strlen(source);
    
    /* Does destination's start overlap source's length */
    overlap = source <= destination && destination <= source + length;

    /* Does destination's end overlap source's length */
    end = destination + size - 1;
    overlap |= source <= end && end <= source + length;
    
    /* No overlap */
    return overlap ? true : false;
}
