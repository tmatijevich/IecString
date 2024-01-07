/*******************************************************************************
 * File: replace.c
 * Created: 2022-08-03
 * 
 * Authors: 
 *   Tyler Matijevich
 * 
 * License:
 *   This file replace.c is part of the IecString project 
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

/* Find in source and replace in destination */
int32_t IecStringReplace(char *destination, uint32_t size, char *source, 
                        char *find, char *replace) {
#ifndef IECSTRING_NOCHECK
    /* Gaurd null pointers */
    if (!destination || !source || !find || !replace)
        return IECSTRING_ERROR_NULL;

    /* Check for zero size*/
    if (!size)
        return IECSTRING_ERROR_SIZE;
#endif

    /* Store lengths */
    size_t source_length = strlen(source);
    size_t find_length = strlen(find);
    size_t replace_length = strlen(replace);
    
#ifndef IECSTRING_NOCHECK
    /* Check if source overlaps destination size */
    if (destination <= source && source < destination + size)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if destination overlaps source length */
    if (source <= destination && destination <= source + source_length)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if find overlaps destination size */
    if (destination <= find && find < destination + size)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if destination overlaps find length */
    if (find <= destination && destination <= find + find_length)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if replace overlaps destination size */
    if (destination <= replace && replace < destination + size)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if destination overlaps replace length */
    if (replace <= destination && destination <= replace + replace_length)
        return IECSTRING_ERROR_OVERLAP;
#endif

    /* Find and replace, otherwise copy */
    uint32_t i = 0;
    size_t min_chars;
    while (*source && i < size - 1) {
        /* Do not compare source against find if not enough characters left*/
        if (source_length - i < find_length) {
            *destination++ = *source++;
            i++;
            continue;
        }

        /* Compare source against find */
        if (strncmp(source, find, find_length) == 0) {
            strncpy(destination, replace, size - 1 - i);
            min_chars = MIN(replace_length, size - 1 - i);
            destination += min_chars;
            source += find_length;
            i += min_chars;
            continue;
        }

        /* Copy character */
        *destination++ = *source++;
        i++;
    }
    
    /* Add null terminator */
    *destination = '\0';
    
    /* Output is truncated is source characters remain after
    writing size bytes to desitnation */
    return IECSTRING_WARNING_TRUNCATE * (*source && i == size - 1);
}
