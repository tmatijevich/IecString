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

#define TOKENS "yMdHhmstf"
#define DELIMETERS "-_ .,/:;()[]"
#define DEFAULT_FORMAT "yyyy-MM-dd HH:mm"

/* Format the current date and/or time */
int32_t IecStringDateTime(char *destination, uint32_t size,
                          DTStructure *value, char *format)
{
    /* Gaurd null pointers */
    if (!destination)
        return IECSTRING_ERROR_NULL;

    /* Check for zero size */
    if (!size)
        return IECSTRING_ERROR_SIZE_ZERO;

    /* Apply default format */
    /* if null pointer */
    if (!format)
        format = DEFAULT_FORMAT;

    /* or if empty string */
    if (!(*format))
        format = DEFAULT_FORMAT;

    /* Check if source overlaps destination size */
    if (destination <= format && format < destination + size)
        return IECSTRING_ERROR_OVERLAP;

    /* Check if destination overlaps source length */
    if (format <= destination && destination <= format + strlen(format))
        return IECSTRING_ERROR_OVERLAP;

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
        "Dec"};
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
        "December"};
    const char day_text_abbreviation[][3] = {
        "Su",
        "M",
        "Tu",
        "W",
        "Th",
        "F",
        "Sa"};
    const char day_text_full[][10] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"};

    while (*format && bytes_remaining > 1)
    {
        /* Does format match any tokens or delimeters? */
        match_count = strspn(format, TOKENS DELIMETERS);

        /* Continue loop if nothing matches */
        if (!match_count)
        {
            format++;
            continue;
        }

        /* Enter a do-while in order to break and continue the parent while */
        do
        {
            /* Match delimeters */
            match_count = strspn(format, DELIMETERS);
            if (match_count)
            {
                /* Copy up to match_count delimeter characters from format */
                IecStringCopy(destination,
                              MIN(bytes_remaining, match_count + 1),
                              format);
                /* "Break" do-while */
                continue;
            }

            /* Match year: yy yyyy */
            match_count = strspn(format, "y");
            switch (match_count)
            {
            case 0:
                /* Break switch to attempt more matches */
                break;
            case 2:
                IecStringDecimal(destination, bytes_remaining,
                                 value->year % 100,
                                 match_count, IECSTRING_FLAG_NONE);
                continue;
            case 4:
                IecStringDecimal(destination, bytes_remaining,
                                 value->year, match_count, IECSTRING_FLAG_NONE);
            default:
                /* "Break" do-while */
                continue;
            }

            /* Match month: M MM MMM MMMM */
            match_count = strspn(format, "M");
            value->month = MIN(MAX(1, value->month), 12);
            switch (match_count)
            {
            case 0:
                /* Break switch to attempt more matches */
                break;
            case 1:
                /* Go to case 2 */
            case 2:
                IecStringDecimal(destination, bytes_remaining,
                                 value->month,
                                 match_count, IECSTRING_FLAG_NONE);
                continue;
            case 3:
                IecStringCopy(destination, bytes_remaining,
                              (char *)month_text_abbreviation[value->month]);
                continue;
            case 4:
                IecStringCopy(destination, bytes_remaining,
                              (char *)month_text_full[value->month]);
            default:
                /* "Break" do-while */
                continue;
            }

            /* Match day: d dd ddd dddd */
            match_count = strspn(format, "d");
            value->wday = MIN(value->wday, 6);
            switch (match_count)
            {
            case 0:
                /* Break switch to attempt more matches */
                break;
            case 1:
                /* Go to case 2 */
            case 2:
                IecStringDecimal(destination, bytes_remaining,
                                 value->day,
                                 match_count, IECSTRING_FLAG_NONE);
                continue;
            case 3:
                IecStringCopy(destination, bytes_remaining,
                              (char *)day_text_abbreviation[value->wday]);
                continue;
            case 4:
                IecStringCopy(destination, bytes_remaining,
                              (char *)day_text_full[value->wday]);
            default:
                /* "Break" do-while */
                continue;
            }

            /* Match 24 hour: H HH */
            match_count = strspn(format, "H");
            switch (match_count)
            {
            case 0:
                /* Break switch to attempt more matches */
                break;
            case 1:
                /* Go to case 2 */
            case 2:
                IecStringDecimal(destination, bytes_remaining,
                                 value->hour,
                                 match_count, IECSTRING_FLAG_NONE);
            default:
                /* "Break" do-while */
                continue;
            }

            /* Match 12 hour: h hh */
            match_count = strspn(format, "h");
            switch (match_count)
            {
            case 0:
                /* Break switch to attempt more matches */
                break;
            case 1:
                /* Go to case 2 */
            case 2:
                IecStringDecimal(destination, bytes_remaining,
                                 value->hour % 12,
                                 match_count, IECSTRING_FLAG_NONE);
            default:
                /* "Break" do-while */
                continue;
            }

            /* Match minuite: m mm */
            match_count = strspn(format, "m");
            switch (match_count)
            {
            case 0:
                /* Break switch to attempt more matches */
                break;
            case 1:
                /* Go to case 2 */
            case 2:
                IecStringDecimal(destination, bytes_remaining,
                                 value->minute,
                                 match_count, IECSTRING_FLAG_NONE);
            default:
                /* "Break" do-while */
                continue;
            }

            /* Match seconds: s ss */
            match_count = strspn(format, "s");
            switch (match_count)
            {
            case 0:
                /* Break switch to attempt more matches */
                break;
            case 1:
                /* Go to case 2 */
            case 2:
                IecStringDecimal(destination, bytes_remaining,
                                 value->second,
                                 match_count, IECSTRING_FLAG_NONE);
            default:
                /* "Break" do-while */
                continue;
            }

            /* Match morning/afternoon: tt */
            match_count = strspn(format, "t");
            switch (match_count)
            {
            case 0:
                /* Break switch to attempt more matches */
                break;
            case 2:
                IecStringCopy(destination, bytes_remaining,
                              value->hour >= 12 ? "PM" : "AM");
            default:
                /* "Break" do-while */
                continue;
            }

            /* Match milliseconds: ff fff */
            match_count = strspn(format, "f");
            switch (match_count)
            {
            case 0:
                /* Break switch to attempt more matches */
                break;
            case 2:
                IecStringDecimal(destination, bytes_remaining,
                                 value->millisec / 10,
                                 match_count, IECSTRING_FLAG_NONE);
                continue;
            case 3:
                IecStringDecimal(destination, bytes_remaining,
                                 value->millisec,
                                 match_count, IECSTRING_FLAG_NONE);
            default:
                /* "Break" do-while */
                continue;
            }
        } while (0);

        current_length = strlen(destination);
        destination += current_length;
        bytes_remaining -= current_length;
        /* Protect missed match count */
        format += MAX(match_count, 1);
    }

    /* Add null terminator */
    *destination = '\0';

    /* Truncated if source characters remain and destination is full */
    return IECSTRING_WARNING_TRUNCATE * (*format && bytes_remaining <= 1);
}
