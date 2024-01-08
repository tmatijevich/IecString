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
#endif 

    size_t source_length = strlen(source);

#ifndef IECSTRING_NOCHECK
    /* Check if source overlaps destination size */
    if (destination <= source && source < destination + size)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if destination overlaps source length */
    if (source <= destination && destination <= source + source_length)
        return IECSTRING_ERROR_OVERLAP;
#endif

    size_t destination_length = strlen(destination);

    /* Append size - 1 - destination_length characters */
    strncpy(destination + destination_length, source, 
            size - 1 - destination_length);

    /* Add null terminator */
    destination[size - 1] = '\0';
    
    /* Warn about truncation if source length exceeds size */
    return IECSTRING_WARNING_TRUNCATE * 
            (source_length > size - 1 - destination_length);
}
