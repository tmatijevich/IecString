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

uint32_t FormatDateTimeToken(char *destination, uint32_t chars_remaining,
                            char *format, DTStructure date_time);

/* Format the current date and/or time */
int32_t IecStringDateTime(char *destination, uint32_t size, char *format) {
    
    /* Local variables */
    const char tokens[] = "yMdHhmstf";
    const char delimeters[] = "-_ .,/:;()[]";
    const char default_format[] = "yyyy-MM-dd HH:mm";
    char next_char;
    uint32_t count, length, chars_remaining = size - 1;
    DTStructureGetTime_typ get_date_time;
    DTStructure date_time;

    /* Verify parameters */
    if (destination == NULL)
        return IECSTRING_ERROR_NULL;

    if (size == 0)
        return IECSTRING_ERROR_SIZE;

    if (format == NULL)
        format = (char*)default_format;

    if (*format == '\0')
        format = (char*)default_format;

    get_date_time.enable = true;
    get_date_time.pDTStructure = (uint32_t)&date_time;
    DTStructureGetTime(&get_date_time);

    while (*format != '\0' && chars_remaining) {
        *destination = '\0';
        count = strspn(format, tokens);
        if (count) 
            length = FormatDateTimeToken(destination, chars_remaining,
                                        format, date_time);
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

/* Format date/time component */
uint32_t FormatDateTimeToken(char *destination, uint32_t chars_remaining,
                            char *format, DTStructure date_time) {
    /* Local variables */
    uint8_t count;
    char temp[13];

    /* y two digit yy two digit zero padded yyyy year */
    count = strspn(format, "y");
    switch (count) {
        case 1:
            if (date_time.year > 2000) date_time.year -= 2000;
            brsitoa(date_time.year, (uint32_t)temp);
            return strlen(strncat(destination, temp, chars_remaining));
        case 2:
            if (date_time.year > 2000) date_time.year -= 2000;
            if (count = date_time.year < 10)
                strncat(destination, "0", chars_remaining);
            brsitoa(date_time.year, (uint32_t)temp);
            return strlen(strncat(destination, temp, chars_remaining - 1)) 
                    + count;
        case 4:
            brsitoa(date_time.year, (uint32_t)temp);
            return strlen(strncat(destination, temp, chars_remaining));
        default:
            break;
    }

    return 0;
}
