/*******************************************************************************
 * File: concat.c
 * Created: 2022-08-03
 * 
 * Contributors: 
 * - Tyler Matijevich
 * 
 * License:
 *  This file concat.c is part of the IecString project released under the
 *  GNU General Public License v3.0 agreement.  For more information, please 
 *  visit https://github.com/tmatijevich/IecString/blob/main/LICENSE.
 ******************************************************************************/

#include "main.h"

/* Concatenate source to destination up to size of destination or source 
length */
int32_t IecStringConcat(char *destination, uint32_t size, char *source) {
    
    /* Local variables */
    uint32_t length;
    
    /* Verify parameters */
    if(destination == NULL || source == NULL)
        return IECSTRING_ERROR_NULL;
    
    if(size == 0)
        return IECSTRING_ERROR_SIZE;
    
    if(Overlap(destination, size, source))
        return IECSTRING_ERROR_OVERLAP;
        
    /* Use string library to append the first size - 1 - length characters */
    length = strlen(destination);
    strncat(destination, source, size - 1 - length);
    
    /* Warn of truncation if combined length exceeds size */
    return IECSTRING_WARNING_TRUNCATE * (length + strlen(source) > size - 1);
}
