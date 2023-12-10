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

uint32_t FormatDateTimeToken(char *destination, uint32_t bytes_remaining,
                            char *format, DTStructure date_time, uint8_t count);

/* Format the current date and/or time */
int32_t IecStringDateTime(char *destination, uint32_t size, 
                            char *format, DTStructure *date_time) {
    
    /* Local variables */
    const char tokens[] = "yMdHhmstf";
    const char delimeters[] = "-_ .,/:;()[]";
    const char default_format[] = "yyyy-MM-dd HH:mm";
    char next_char;
    uint32_t match, length, chars_remaining = size - 1;

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
        match = strspn(format, tokens);
        if (match) {
            match = FormatDateTimeToken(destination, chars_remaining + 1,
                                        format, *date_time, match);
            length = strlen(destination);
        }
        else {
            next_char = *format;
            match = 1;
            if(strspn(&next_char, delimeters)) {
                strncat(destination, "_", chars_remaining);
                length = 1;
            }
            else
                length = 0;
        }
        destination += length;
        chars_remaining -= length;
        format += match;
    }

    *destination = '\0';
    
    return 0;
}

/* Format date/time token */
uint32_t FormatDateTimeToken(char *destination, uint32_t bytes_remaining,
                            char *format, DTStructure date_time, 
                            uint8_t count) {
    /* Local variables */
    uint8_t match;
    char month_abv[][4] = {"N/A", "Jan", "Feb", "Mar", "Apr", "May", 
                            "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", 
                            "Dec"};
    char month_full[][10] = {"N/A", "January", "February", "March", "April", 
                            "May", "June", "July", "August", "September", 
                            "October", "November", "December"};

    /* yy yyyy year */
    match = strspn(format, "y");
    switch (match) {
        case 0:
            break;
        case 2:
            IecStringPadInt(destination, bytes_remaining, 
                            date_time.year % 100, 2, 0);
            return match;
        case 4:
            IecStringPadInt(destination, bytes_remaining, date_time.year, 4, 0);
            return match;
        default:
            return match;
    }

    /* M MM MMM MMMM month */
    match = strspn(format, "M");
    if (date_time.month < 1) date_time.month = 1;
    else if (date_time.month > 12) date_time.month = 12;
    switch (match) {
        case 0:
            break;
        case 1:
        case 2:
            IecStringPadInt(destination, bytes_remaining, 
                            date_time.month, match, 0);
            return match;
        case 3:
            IecStringCopy(destination, bytes_remaining, 
                            month_abv[date_time.month]);
            return match;
        case 4:
            IecStringCopy(destination, bytes_remaining, 
                            month_full[date_time.month]);
            return match;
        default:
            return match;
    }

    return count;
}
