/*******************************************************************************
 * File: format.c
 * Created: 2020-05-05
 * 
 * Contributors: 
 * - Tyler Matijevich
 * 
 * License:
 *  This file format.c is part of the IecString project released under the
 *  GNU General Public License v3.0 agreement.  For more information, please 
 *  visit https://github.com/tmatijevich/IecString/blob/main/LICENSE.
 ******************************************************************************/

#include "main.h"

/* Format string with runtime data */
int32_t IecStringFormat(char *destination, uint32_t size, char *source, 
                        IecStringFormatType *values) {
    
    /* Local variables */
    const char bool_text[][6] = {"FALSE", "TRUE"};
    uint8_t bool_index;
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
        
        /* Temporarily add null terminator to perform concatenation */
        *destination = '\0';
        
        /* Reset length */
        length = 0;
        
        switch (*(++source)) {
            case 'b':
                if (count_bool <= IECSTRING_FORMAT_INDEX) {
                    bool_index = values->b[count_bool++] > 0 ? true : false;
                    length = strlen(strncat(destination, 
                                            bool_text[bool_index], 
                                            bytes_remaining));
                }
                break;
                
            case 'f':
                if (count_float <= IECSTRING_FORMAT_INDEX) {
                    brsftoa((float)values->f[count_float++], 
                            (uint32_t)number_text);
                    length = strlen(strncat(destination, 
                                            number_text, 
                                            bytes_remaining));
                }
                break;
                
            case 'i':
                if (count_int <= IECSTRING_FORMAT_INDEX) {
                    brsitoa(values->i[count_int++], (uint32_t)number_text);
                    length = strlen(strncat(destination, 
                                            number_text, 
                                            bytes_remaining));
                }
                break;
                
            case 's':
                if (count_string <= IECSTRING_FORMAT_INDEX) 
                    length = strlen(strncat(destination, 
                                            values->s[count_string++], 
                                            bytes_remaining));
                break;
                
            case '%':
                *destination = '%';
                length = 1;
                break;
        }
        
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
