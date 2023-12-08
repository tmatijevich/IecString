/*******************************************************************************
 * File: date_time.c
 * Created: 2023-12-08
 * 
 * Authors: 
 *   Tyler Matijevich
 * 
 * License:
 *   This file date_time.c is part of the IecString project 
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

/* Format the current date and/or time */
int32_t IecStringDateTime(char *destination, uint32_t size, char *format) {
    
    /* Local variables */
    const char tokens[] = "yMdHhmstf";
    const char delimeters[] = "-_ .,/:;()[]";
    const char default_format[] = "yyyy-MM-dd HH:mm";
    char next_char;
    uint32_t count, copy, length, chars_remaining = size - 1;

    /* Verify parameters */
    if (destination == NULL)
        return IECSTRING_ERROR_NULL;

    if (size == 0)
        return IECSTRING_ERROR_SIZE;

    if (format == NULL)
        format = (char*)default_format;

    if (*format == '\0')
        format = (char*)default_format;

    while (*format != '\0' && chars_remaining) {
        *destination = '\0';
        count = strspn(format, tokens);
        if (count) {
            copy = count;
            if (count > 4) copy = 4;
            length = strlen(strncat(destination, "XXXX", 
                                    MIN(copy, chars_remaining)));
        }
        else {
            next_char = *format;
            count = 1;
            if(strspn(&next_char, delimeters)) {
                strncat(destination, "_", chars_remaining);
                length = 1;
            }
            else
                length = 0;
        }
        destination += length;
        chars_remaining -= length;
        format += count;
    }

    *destination = '\0';
    
    return 0;
}
