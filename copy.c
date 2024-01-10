/*******************************************************************************
 * File: copy.c
 * Created: 2022-08-03
 * 
 * Authors: 
 *   Tyler Matijevich
 * 
 * License:
 *   This file copy.c is part of the IecString project 
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

/* Copy source to destination up to size of destination or source length */
int32_t IecStringCopy(char *destination, uint32_t size, char *source) {
    
    /* Gaurd null pointers */
    if (!destination || !source)
        return IECSTRING_ERROR_NULL;
    
    /* Check for zero size */
    if (!size)
        return IECSTRING_ERROR_SIZE;

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
    
    /* Copy the safe and optimal number of characters */
    size_t min_char_count = MIN(size - 1, source_length);
    strncpy(destination, source, min_char_count);
    
    /* Add null terminator */
    destination[min_char_count] = '\0';
    
    /* Warn if truncated when source length exceeds size */
    return IECSTRING_WARNING_TRUNCATE * (source_length > size - 1);
}

/* Copy without safety checks for private use */
char* FastCopy(char *destination, uint32_t size, char *source) {
    /* Skip:
       - Null pointer checks
       - Destination size check
       - Memory overlap check
       - Truncation warning check
    */
    
    /* Copy and decrement size first to ensure byte for null terminator */
    while (--size && *source != '\0')
        *destination++ = *source++;
    
    /* Null terminator */
    *destination = '\0';
    return destination;
}
