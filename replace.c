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

#include "main.h"

/* Find in source and replace in destination */
int32_t IecStringReplace(char *destination, uint32_t size, char *source,
                         char *find, char *replace)
{
    /* Gaurd null pointers */
    if (!destination || !source || !find || !replace)
        return IECSTRING_ERROR_NULL;

    /* Check for zero size*/
    if (!size)
        return IECSTRING_ERROR_SIZE_ZERO;

    /* Store lengths */
    size_t source_length = strlen(source);
    size_t find_length = strlen(find);
    size_t replace_length = strlen(replace);

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

    /* Find and replace, otherwise copy */
    uint32_t i = 0;
    size_t min_char_count;
    while (*source && i < size - 1)
    {
        /* Break if nothing to find or not enough characters left to compare */
        if (find_length == 0 || source_length - i < find_length)
        {
            strncpy(destination, source, size - 1 - i);
            min_char_count = MIN(source_length, size - 1 - i);
            destination += min_char_count;
            source += min_char_count;
            break;
        }

        /* Compare source against find */
        if (strncmp(source, find, find_length) == 0)
        {
            strncpy(destination, replace, size - 1 - i);
            min_char_count = MIN(replace_length, size - 1 - i);
            destination += min_char_count;
            source += find_length;
            i += min_char_count;
            continue;
        }

        /* Copy character */
        *destination++ = *source++;
        i++;
    }

    /* Add null terminator */
    *destination = '\0';

    /* Truncated if source characters remain and destination is full */
    return IECSTRING_WARNING_TRUNCATE * (*source && i == size - 1);
}
