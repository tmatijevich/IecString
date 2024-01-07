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

/* Concatenate source to destination up to size of destination or source 
length */
int32_t IecStringConcat(char *destination, uint32_t size, char *source) {
    
#ifndef IECSTRING_NOCHECK
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
    if (source <= destination && destination <= source + strlen(source))
        return IECSTRING_ERROR_OVERLAP;
#endif

    /* Read length of destination to subtract from size and shift pointer */
    size_t length = strlen(destination);
    size -= length;
    destination += length;

    /* Concatenate characters */
    while (--size && *source)
        *destination++ = *source++;
    
    /* Add null terminator */
    *destination = '\0';
    
    /* Output is truncated is source characters remain after
    writing up to size bytes to desitnation */
    return IECSTRING_WARNING_TRUNCATE * (*source && !size);
}
