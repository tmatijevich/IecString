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

#ifndef IECSTRING_STANDALONE
#include <IecString.h>
#else
#include "type.h"
int32_t IecStringCopy(char *destination, uint32_t size, char *source);
int32_t IecStringFloat(char *destination, uint32_t size, float value);
int32_t IecStringDecimal(char *destination, uint32_t size, int32_t value, 
                        uint8_t width, unsigned char pad);
#endif

#include <stdint.h>
#include <string.h>

/* Format string with runtime data */
int32_t IecStringFormat(char *destination, uint32_t size, char *source, 
                        IecStringFormatType *values) {
    
    /* Gaurd null pointers */
    if (!destination || !source || !values)
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
        
    /* Local variables */
    int count_bool = 0, count_float = 0, count_int = 0, count_string = 0;
    uint32_t bytes_remaining = size;
    size_t length;

    /* Format each character from source */
    while (*source && bytes_remaining > 1) {
        /* Directly copy source character if it is not a specifier */
        if (*source != '%') {
            *destination++ = *source++;
            bytes_remaining--;
            continue;
        }

        /* Force string length of zero if nothing is written */
        *destination = '\0';
        
        switch (*(++source)) {
            case 'b':
                if (count_bool > IECSTRING_FORMAT_INDEX)
                    break;
                
                IecStringCopy(destination, bytes_remaining, 
                                values->b[count_bool++] ? "TRUE" : "FALSE");
                break;
                
            /* LREAL/double casted to REAL/float */
            case 'r':
            case 'f':
                if (count_float > IECSTRING_FORMAT_INDEX)
                    break;

                IecStringFloat(destination, bytes_remaining, 
                                (float)values->f[count_float++]);
                break;
                
            case 'i':
                if (count_int > IECSTRING_FORMAT_INDEX)
                    break;

                IecStringDecimal(destination, bytes_remaining, 
                                values->i[count_int++], 0, 0);
                break;
                
            case 's':
                if (count_string > IECSTRING_FORMAT_INDEX)
                    break;

                IecStringCopy(destination, bytes_remaining, 
                                values->s[count_string++]);
                break;
                
            case '%':
                IecStringCopy(destination, bytes_remaining, "%");
                break;
        }
        
        length = strlen(destination);
        destination += length;
        bytes_remaining -= length;
        source++;
    }
    
    /* Add null terminator */
    *destination = '\0';
    
    /* Warn if truncated when source characters remain unwritten */
    return IECSTRING_WARNING_TRUNCATE * (*source && bytes_remaining <= 1);
}
