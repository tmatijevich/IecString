/*******************************************************************************
 * File: split.c
 * Created: 2024-04-03
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file split.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

/* Split source into tokens */
int32_t IecStringSplit(char *destination, uint32_t size, char *source,
                       char *delimeters, uint32_t *address)
{
    /* Gaurd null pointers */
    if (!destination || !source || !delimeters)
        return IECSTRING_ERROR_NULL;

    /* Check for zero size */
    if (!size)
        return IECSTRING_ERROR_SIZE_ZERO;

    /* Check if source overlaps destination size */
    if (destination <= source && source < destination + size)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if destination overlaps source length */
    size_t length = strlen(source);
    if (source <= destination && destination <= source + length)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if delimeters overlaps destination size */
    if (destination <= delimeters && delimeters < destination + size)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if destination overlaps delimeters length */
    length = strlen(delimeters);
    if (delimeters <= destination && destination <= delimeters + length)
        return IECSTRING_ERROR_OVERLAP;

    /* Return the number of characters in the initial portion containing 
       only delimeters */
    size_t length_before = strspn(source, delimeters);

    /* Return the number of characters before the first occurrence 
       of any delimeter */
    size_t token_length = strcspn(source + length_before, delimeters);

    /* Copy the safe and optimal number of characters */
    size_t minimum = MIN(size - 1, token_length);
    strncpy(destination, source + length_before, minimum);

    /* Add null terminator */
    destination[minimum] = '\0';

    /* Determine the delimeter length after and set the next read address */
    char* read = source + length_before + token_length;
    read += strspn(read, delimeters);
    if (address)
        *address = *read ? (uint32_t)read : 0;

    /* Truncated if token length exceeds size */
    return IECSTRING_WARNING_TRUNCATE * (token_length > size - 1);
}
