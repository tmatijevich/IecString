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
int32_t IecStringReplace(char *destination, uint32_t size, char *find, 
                        char *replace, char *source) {
    
    /* Local variables */
    uint32_t find_length, replace_length, offset = 0, min_length;
    
    /* Verify parameters */
    if (destination == NULL || find == NULL || 
        replace == NULL || source == NULL)
        return IECSTRING_ERROR_NULL;
    
    if (size == 0)
        return IECSTRING_ERROR_SIZE;
    
    if (Overlap(destination, size, find) || 
        Overlap(destination, size, replace) || 
        Overlap(destination, size, source))
        return IECSTRING_ERROR_OVERLAP;
    
    find_length = strlen(find);
    if (find_length > strlen(source) || find_length == 0)
        return IECSTRING_ERROR_LENGTH;
    
    /* Find and replace */
    replace_length = strlen(replace);
    while (offset < size - 1) {
        /* End of source */
        if (*source == '\0')
            break;
            
        /* Compare */
        else if (strncmp(source, find, find_length) == 0) {
            IecStringCopy(destination, size - offset, replace);
            /* Count full or truncated length*/
            min_length = MIN(replace_length, size - offset - 1);
            destination += min_length;
            offset += min_length;
            source += find_length;
        }
        
        /* Copy */
        else {
            *destination++ = *source++;
            offset++;
        }
    }
    
    /* Null terminator */
    *destination = '\0';
    
    /* Truncated if source characters remain and no bytes left */
    return IECSTRING_WARNING_TRUNCATE * (*source != '\0' && offset == size - 1);
}
