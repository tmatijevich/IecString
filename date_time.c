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

#define TOKENS "yMdHhmstf"
#define DELIMETERS "-_ .,/:;()[]"

/* Format the current date and/or time */
int32_t IecStringDateTime(char *destination, uint32_t size, 
                            char *format, DTStructure *date_time) {
    
    /* Local variables */
    const char tokens[] = "yMdHhmstf";
    const char delimiters[] = "-_ .,/:;()[]";
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
    
    else if (Overlap(destination, size, format))
        return IECSTRING_ERROR_OVERLAP;

    if (*format == '\0')
        format = (char*)default_format;

    int match_count;
    uint32_t bytes_remaining = size;
    size_t current_length;

    const char month_text_abbreviation[][4] = {
        "N/A",
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };
    const char month_text_full[][10] = {
        "N/A",
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };
    const char day_abv[][3] = {"Su", "M", "Tu", "W", "Th", "F", "Sa"};
    const char day_full[][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", 
                                "Thursday", "Friday", "Saturday"};

    while (*format && bytes_remaining > 1) {
        /* Does format match any tokens or delimeters? */
        match_count = strspn(format, TOKENS DELIMETERS);

        /* Continue loop if nothing matches */
        if (!match_count) {
            format++;
            continue;
        }

        /* Enter a do-while in order to break and continue the parent while */
        do {
            /* Match delimeters */
            match_count = strspn(format, DELIMETERS);
            if (match_count) {
                /* Copy up to match_count delimeter characters from format */
                IecStringCopy(destination, 
                              MIN(bytes_remaining, match_count + 1),
                              format);
                /* "Break" do-while */
                continue;
            }

            /* Match year: yy yyyy */
            match_count = strspn(format, "y");
            switch (match_count) {
                case 0:
                    /* Break switch to attempt more matches */
                    break;
                case 2:
                    IecStringDecimal(destination, bytes_remaining, 
                                     date_time->year % 100, match_count, 0);
                    continue;
                case 4:
                    IecStringDecimal(destination, bytes_remaining, 
                                     date_time->year, match_count, 0);
                default:
                    /* "Break" do-while */
                    continue;
            }

            /* Match month: M MM MMM MMMM */
            match_count = strspn(format, "M");
            date_time->month = MIN(MAX(1, date_time->month), 12);
            switch (match_count) {
                case 0:
                    /* Break switch to attempt more matches */
                    break;
                case 1:
                    /* Go to case 2 */
                case 2:
                    IecStringDecimal(destination, bytes_remaining, 
                                     date_time->month, 
                                     match_count, '0');
                    continue;
                case 3:
                    IecStringCopy(destination, bytes_remaining, 
                                  month_text_abbreviation[date_time->month]);
                    continue;
                case 4:
                    IecStringCopy(destination, bytes_remaining, 
                                  month_text_full[date_time->month]);
                default:
                    /* "Break" do-while */
                    continue;
            }
        }
        while (0);

        current_length = strlen(destination);
        destination += current_length;
        bytes_remaining -= current_length;
        /* Protect missed match count */
        format += MAX(match_count, 1);
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
    const char month_abv[][4] = {"N/A", "Jan", "Feb", "Mar", "Apr", "May", 
                            "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", 
                            "Dec"};
    const char month_full[][10] = {"N/A", "January", "February", "March", "April", 
                            "May", "June", "July", "August", "September", 
                            "October", "November", "December"};
    const char day_abv[][3] = {"Su", "M", "Tu", "W", "Th", "F", "Sa"};
    const char day_full[][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", 
                                "Thursday", "Friday", "Saturday"};

    /* yy yyyy year */
    match = strspn(format, "y");
    switch (match) {
        case 0:
            break;
        case 2:
            IecStringDecimal(destination, bytes_remaining, 
                            date_time.year % 100, 2, 0);
            return match;
        case 4:
            IecStringDecimal(destination, bytes_remaining, date_time.year, 4, 0);
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
            IecStringDecimal(destination, bytes_remaining, 
                            date_time.month, match, 0);
            return match;
        case 3:
            FastCopy(destination, bytes_remaining, 
                    (char*)month_abv[date_time.month]);
            return match;
        case 4:
            FastCopy(destination, bytes_remaining, 
                    (char*)month_full[date_time.month]);
            return match;
        default:
            return match;
    }

    /* d dd ddd dddd day */
    match = strspn(format, "d");
    if (date_time.wday > 6) date_time.wday = 6;
    switch (match) {
        case 0:
            break;
        case 1:
        case 2:
            IecStringDecimal(destination, bytes_remaining, 
                            date_time.day, match, 0);
            return match;
        case 3:
            FastCopy(destination, bytes_remaining, 
                    (char*)day_abv[date_time.wday]);
            return match;
        case 4:
            FastCopy(destination, bytes_remaining, 
                    (char*)day_full[date_time.wday]);
            return match;
        default:
            return match;
    }

    /* H HH 24 hour */
    match = strspn(format, "H");
    switch (match) {
        case 0:
            break;
        case 1:
        case 2:
            IecStringDecimal(destination, bytes_remaining, 
                            date_time.hour, match, 0);
            return match;
        default:
            return match;
    }

    /* h hh 12 hour */
    match = strspn(format, "h");
    switch (match) {
        case 0:
            break;
        case 1:
        case 2:
            IecStringDecimal(destination, bytes_remaining, 
                            date_time.hour % 12, match, 0);
            return match;
        default:
            return match;
    }

    /* m mm minute */
    match = strspn(format, "m");
    switch (match) {
        case 0:
            break;
        case 1:
        case 2:
            IecStringDecimal(destination, bytes_remaining, 
                            date_time.minute, match, 0);
            return match;
        default:
            return match;
    }

    /* s ss second */
    match = strspn(format, "s");
    switch (match) {
        case 0:
            break;
        case 1:
        case 2:
            IecStringDecimal(destination, bytes_remaining, 
                            date_time.second, match, 0);
            return match;
        default:
            return match;
    }

    /* tt morning/afternoon */
    match = strspn(format, "t");
    switch (match) {
        case 0:
            break;
        case 2:
            if (date_time.hour >= 12) FastCopy(destination, bytes_remaining, 
                                                "PM");
            else FastCopy(destination, bytes_remaining, "AM");
            return match;
        default:
            return match;
    }

    /* ff fff milliseconds */
    match = strspn(format, "f");
    switch (match) {
        case 0:
            break;
        case 2:
            IecStringDecimal(destination, bytes_remaining,
                            date_time.millisec / 10, match, 0);
            return match;
        case 3:
            IecStringDecimal(destination, bytes_remaining,
                            date_time.millisec, match, 0);
            return match;
        default:
            return match;
    }

    return count;
}
