/*******************************************************************************
 * File: concat.c
 * Created: 2022-08-03
 * 
 * Authors: 
 *   Tyler Matijevich
 * 
 * License:
 *   This file concat.c is part of the IecString project 
 *   released under the MIT license agreement.
 ******************************************************************************/

#ifndef IECSTRING_STANDALONE
#include <IecString.h>
#else
#include "type.h"
#endif

#include <stdint.h>
#include <string.h>

#define MIN(x,y) (((x) < (y)) ? (x) : (y))

/* Concatenate source to destination up to size of destination 
or source length */
int32_t IecStringConcat(char *destination, uint32_t size, char *source) {
    
    /* Gaurd null pointers */
    if (!destination || !source)
        return IECSTRING_ERROR_NULL;
    
    /* Check for valid size */
    size_t destination_length = strlen(destination);
    if (size <= destination_length)
        return IECSTRING_ERROR_SIZE_INVALID;

    /* Check if source overlaps destination size */
    if (destination <= source && source < destination + size)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if destination overlaps source length */
    size_t source_length = strlen(source);
    if (source <= destination && destination <= source + source_length)
        return IECSTRING_ERROR_OVERLAP;

    /* Performance considerations:
    strncpy performed better than while loop
    strncpy performed better than strncat
    */

    /* Append the safe and optimal number of character */
    size_t min_char_count = MIN(size - 1 - destination_length, source_length);
    strncpy(destination + destination_length, source, min_char_count);

    /* Add null terminator */
    destination[destination_length + min_char_count] = '\0';
    
    /* Warn if truncated when source length exceeds size */
    return IECSTRING_WARNING_TRUNCATE * 
            (source_length > size - 1 - destination_length);
}
