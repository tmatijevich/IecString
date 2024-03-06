/*******************************************************************************
 * File: format.c
 * Created: 2020-05-05
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file format.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include <IecString.h>
#include <stdint.h>
#include <string.h>

/* Format string with runtime data */
int32_t IecStringFormat(char *destination, uint32_t size, char *source,
                        IecStringFormatType *values)
{
    /* Gaurd null pointers */
    if (!destination || !source || !values)
    {
        /* Copy if no values */
        IecStringCopy(destination, size, source);
        return IECSTRING_ERROR_NULL;
    }

    /* Check for zero size */
    if (!size)
        return IECSTRING_ERROR_SIZE_ZERO;

    /* Check if source overlaps destination size */
    if (destination <= source && source < destination + size)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if destination overlaps source length */
    if (source <= destination && destination <= source + strlen(source))
        return IECSTRING_ERROR_OVERLAP;

    /* Local variables */
    int count_bool = 0, count_float = 0, count_int = 0, count_string = 0;
    uint32_t bytes_remaining = size;
    size_t length;
    int32_t status = 0;

    /* Format each character from source */
    while (*source && bytes_remaining > 1)
    {
        /* Directly copy source character if it is not a specifier */
        if (*source != '%')
        {
            *destination++ = *source++;
            bytes_remaining--;
            continue;
        }

        /* Force string length of zero if nothing is written */
        *destination = '\0';
        status = 0;

        switch (*(++source))
        {
        case 'b':
            if (count_bool > IECSTRING_FORMAT_INDEX)
                break;

            status = IecStringCopy(destination, bytes_remaining,
                                   values->b[count_bool++] ? "TRUE" : "FALSE");
            break;

        /* LREAL/double casted to REAL/float */
        case 'r':
        case 'f':
            if (count_float > IECSTRING_FORMAT_INDEX)
                break;

            status = IecStringFloat(destination, bytes_remaining,
                                    (float)values->f[count_float++], 0, 6, IECSTRING_FLAG_NONE);
            break;

        /* Integer/decimal */
        case 'i':
        case 'd':
            if (count_int > IECSTRING_FORMAT_INDEX)
                break;

            status = IecStringDecimal(destination, bytes_remaining,
                                      values->i[count_int++], 0, IECSTRING_FLAG_NONE);
            break;

        case 's':
            if (count_string > IECSTRING_FORMAT_INDEX)
                break;

            status = IecStringCopy(destination, bytes_remaining,
                                   values->s[count_string++]);
            break;

        case '%':
            *destination = '%';
            *(destination + 1) = '\0';
            break;
        }

        length = strlen(destination);
        destination += length;
        bytes_remaining -= length;
        source++;
    }

    /* Add null terminator */
    *destination = '\0';

    /* Truncated if source characters remain and destination is full
    or function returns a status */
    return IECSTRING_WARNING_TRUNCATE *
           ((*source && bytes_remaining <= 1) || status);
}
