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

#include "main.h"

/* Format string with runtime data */
int32_t IecStringFormat(char *destination, uint32_t size, char *source, 
                        IecStringFormatType *values) {
    
    /* Local variables */
    const char bool_text[][6] = {"FALSE", "TRUE"};
    /* Floats: [<+->]1.23456[e<+->12] = 12 characters + null terminator */
    /* Longs: -2147483648 to 2147483647 = 11 characters + null terminator */
    char number_text[13];
    uint8_t count_bool = 0, count_float = 0, count_int = 0, count_string = 0;
    uint32_t length, bytes_remaining = size - 1;
    
    /* Verify parameters */
    if (destination == NULL || source == NULL || values == NULL)
        return IECSTRING_ERROR_NULL;
    
    if (size == 0)
        return IECSTRING_ERROR_SIZE;
    
    if (Overlap(destination, size, source))
        return IECSTRING_ERROR_OVERLAP;
        
    /* Format */
    while (*source != '\0' && bytes_remaining) {
        
        /* Copy if no specifier */
        if (*source != '%') {
            *destination++ = *source++;
            bytes_remaining--;
            continue;
        }

        /* Default to zero length */
        *destination = '\0';
        
        switch (*(++source)) {
            case 'b':
                if (count_bool <= IECSTRING_FORMAT_INDEX)
                    FastCopy(destination, bytes_remaining + 1, 
                            (char*)bool_text[values->b[count_bool++] > 0]);
                break;
                
            case 'f':
                if (count_float <= IECSTRING_FORMAT_INDEX) {
                    brsftoa((float)values->f[count_float++], 
                            (uint32_t)number_text);
                    FastCopy(destination, bytes_remaining + 1, number_text);
                }
                break;
                
            case 'i':
                if (count_int <= IECSTRING_FORMAT_INDEX)
                    IecStringInteger(destination, bytes_remaining + 1, 
                        values->i[count_int++], 0, 0);
                break;
                
            case 's':
                if (count_string <= IECSTRING_FORMAT_INDEX)
                    FastCopy(destination, bytes_remaining + 1, 
                            values->s[count_string++]);
                break;
                
            case '%':
                FastCopy(destination, bytes_remaining + 1, "%");
                break;
        }
        
        length = strlen(destination);
        destination += length;
        bytes_remaining -= length;
        source++;
    }
    
    /* Null terminator */
    *destination = '\0';
    
    /* Truncated if source characters remain and no bytes left */
    return IECSTRING_WARNING_TRUNCATE * (*source != '\0' && 
        bytes_remaining == 0);
}
