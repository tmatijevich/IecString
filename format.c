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
    uint32_t length, bytes_remaining = size;
    
    /* Verify parameters */
    if (destination == NULL || source == NULL || values == NULL)
        return IECSTRING_ERROR_NULL;
    
    if (size == 0)
        return IECSTRING_ERROR_SIZE;
    
    if (Overlap(destination, size, source))
        return IECSTRING_ERROR_OVERLAP;
        
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
