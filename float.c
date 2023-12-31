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
    int32_t norm_int, exp, i, offset = 0, count, notate, zeros, decimal = 0;
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

    /* Derive normalized value */
    norm_val = value;
    i = 5 - exp;
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
    norm_int = (int32_t)(norm_val + 0.5);
    if (norm_int >= 1000000) {
        norm_int /= 10;
        exp++;
    }

    /* Derive significant digits */
    for (i = 5; i >= 0; i--) {
        digits[i] = norm_int % 10;
        norm_int /= 10;
    }

    /* Write characters */
    /* Use scientific notation */
    notate = exp < -6 || 5 < exp;
    /* Number of significant digits displayed */
    count = 6 * (notate || exp > -2) + (exp + 7) * (!notate && exp < -1);
    /* Number of leading zeros displayed */
    zeros = (0 - exp) * (!notate && exp < 0);

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
