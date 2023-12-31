/*******************************************************************************
 * File: float.c
 * Created: 2023-12-17
 * 
 * Authors: 
 *   Tyler Matijevich
 * 
 * License:
 *   This file float.c is part of the IecString project 
 *   released under the MIT license agreement.
 ******************************************************************************/

#include <IecString.h>
#include "stdint.h"
#include "string.h"

/* Convert floating point number to string */
int32_t IecStringFloat(char *destination, uint32_t size, float value) {
    
    /* Local variables */
    uint8_t digits[6] = {0};
    float norm_val;
    int32_t exp, i, offset = 0, count, notate, zeros, decimal = 0;
    int32_t norm_int, norm_int_max;
    char text[81];

    strcpy(text, "+X.XXXXXXe+XX");

    /* Write sign */
    if (value < 0.0) {
        value *= -1.0f;
        text[offset++] = '-';
    }

    /* Derive exponent */
    norm_val = value;
    exp = 0;
    while (norm_val) {
        if (norm_val >= 10.0f) {
            norm_val /= 10.0f;
            exp++;
            continue;
        }
        if (norm_val < 1.0f) {
            norm_val *= 10.0f;
            exp--;
            continue;
        }
        break;
    }

    /* Count characters */
    /* Use scientific notation */
    notate = exp < -6 || 5 < exp;
    /* Number of significant digits displayed */
    count = 6 * (notate || exp > -2) + (exp + 7) * (!notate && exp < -1);
    /* Number of leading zeros displayed */
    zeros = (0 - exp) * (!notate && exp < 0);

    /* Derive normalized value */
    norm_val = value;
    i = count - 1 - exp;
    while (i) {
        if (i > 0) {
            norm_val *= 10.0f;
            i--;
            continue;
        }
        if (i < 0) {
            norm_val /= 10.0f;
            i++;
            continue;
        }
        break;
    }

    /* Derive maximum integer */
    for (i = 0, norm_int_max = 1; i < count; i++)
        norm_int_max *= 10;
    
    /* Round normalized integer and check rollover */
    norm_int = (int32_t)(norm_val + 0.5);
    if (norm_int >= norm_int_max) {
        /* Rounded value exceeds maximum number of significant digits */
        if (count == 6)
            norm_int /= 10;
        /* Write more significant digits */
        else {
            count++;
            zeros -= zeros > 0;
        }
        exp++;
        /* Recalculate scientific notation flag */
        notate = exp < -6 || 5 < exp;
    }

    /* Derive significant digits */
    for (i = count - 1; i >= 0; i--) {
        digits[i] = norm_int % 10;
        norm_int /= 10;
    }

    /* Write characters */
    do {
        text[offset++] = '0' + digits[decimal] * !zeros;
        decimal += !zeros;
        zeros -= zeros > 0;
    }
    while (!notate && decimal <= exp);

    /* Place decimal if significant digits remain */
    if (decimal < count)
        text[offset++] = '.';

    /* Write remaining significant digits */
    while (decimal < count) {
        text[offset++] = '0' + digits[decimal] * !zeros;
        decimal += !zeros;
        zeros -= zeros > 0;
    }

    text[offset] = '\0';
    if (notate) {
        text[offset++] = 'e';
        IecStringInteger(text + offset, sizeof(text) - offset, exp, 0, ' ');
    }
    IecStringCopy(destination, size, text);

    return 0;
}
