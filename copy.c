/*******************************************************************************
 * File: copy.c
 * Created: 2022-08-03
 * 
 * Contributors: 
 * - Tyler Matijevich
 * 
 * License:
 *  This file copy.c is part of the IecString project released under the
 *  GNU General Public License v3.0 agreement.  For more information, please 
 *  visit https://github.com/tmatijevich/IecString/blob/main/LICENSE.
 ******************************************************************************/

#include "main.h"

/* Copy source to destination up to size of destination or source length */
int32_t IecStringCopy(char *destination, uint32_t size, char *source) {
    
    /* Verify parameters */
    if (destination == NULL || source == NULL)
        return IECSTRING_ERROR_NULL;
    
    if (size == 0)
        return IECSTRING_ERROR_SIZE;
    
    if (Overlap(destination, size, source))
        return IECSTRING_ERROR_OVERLAP;
        
    /* Copy and decrement size first to ensure byte for null terminator */
    while (--size && *source != '\0')
        *destination++ = *source++;
        
    /* Null terminator */
    *destination = '\0';
    
    /* Truncated if source characters remain and no bytes left */
    return IECSTRING_WARNING_TRUNCATE * (*source != '\0' && size == 0);
}
