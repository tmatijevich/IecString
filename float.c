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

#ifndef IECSTRING_STANDALONE
#include <IecString.h>
#else
#include "type.h"
#endif

#include <stdint.h>
#include <string.h>
#include <math.h>

/* Convert floating point number to string */
int32_t IecStringFloat(char *destination, uint32_t size, float value) {
    
    /* Gaurd null pointer */
    if (!destination)
        return IECSTRING_ERROR_NULL;

    /* Check for zero size */
    if (!size)
        return IECSTRING_ERROR_SIZE;
    
    /* Check for insufficient size */
    /* +X.XXXXXe+XX */
    if (size < 13) {
        /* Clear destination */
        *destination = '\0';
        return IECSTRING_ERROR_SIZE;
    }

    /* Check for zeros, infinities, and illegal numbers */
    uint32_t raw = *(uint32_t*)&value;
    uint32_t sign = raw >> 31;
    uint32_t exponent = raw >> 23 & 0xff;
    uint32_t mantissa = raw & 0x7fffff;

    /* Write zero */
    if (!sign && !exponent && !mantissa) {
        strcpy(destination, "0");
        return 0;
    }
    if (sign && !exponent && !mantissa) {
        strcpy(destination, "-0");
        return 0;
    }

    /* Write infinity */
    if (!sign && exponent == 0xff && !mantissa) {
        strcpy(destination, "inf");
        return 0;
    }
    if (sign && exponent == 0xff && !mantissa) {
        strcpy(destination, "-inf");
        return 0;
    }

    /* Write "Not a Number" */
    if (exponent == 0xff) {
        strcpy(destination, "NaN");
        return 0;
    }

    /* Write sign */
    if (sign) {
        *destination++ = '-';
        value *= -1.0f;
    }

    /* Find the base 10 exponent */
    int exp = (int)floorf(log10f(value));

    /* Use scientific notation if exponent > 10^5 or 10^-6 > exponent */
    int sci = exp > 5 || -6 > exp;

    /* Count the number of significant digits displayed up to 6 */
    /* Always display 6 digits unless the exponent is between -2 and -6 */
    int count = -2 >= exp && exp >= -6 ? exp + 7 : 6;

    /* Count leading zeros */
    /* Display leading zeros if exponent is between -1 and -6 */
    int zeros = -1 >= exp && exp >= -6 ? -exp : 0;

    /* Normalize the value so all significant digits 
    are before the decimal point */
    float norm_val = 1.0f;
    for (int i = count - 1 - exp; i != 0; i = i > 0 ? i - 1 : i + 1)
        norm_val *= 10.0f * (i > 0) + 0.1f * (i < 0);
    norm_val *= value;

    /* Calculate the maximum normalized value based on count and store in int */
    int32_t norm_int_max = 1;
    for (int i = 0; i < count; i++)
        norm_int_max *= 10;

    /* Calculate the normalized value based on count
    and round to the nearest whole number */
    int32_t norm_int = (int32_t)roundf(norm_val);
    
    /* Check for rollover after rounding */
    if (norm_int >= norm_int_max) {
        /* Re-normalize the normalized value if exceeding 6 digits */
        norm_int = count == 6 ? norm_int / 10 : norm_int;
        /* Increase the exponent */
        exp++;
        /* Decrease number of zeros if less than 6 digits 
        or exponent is now zero */
        zeros -= zeros > 0 && (count < 6 || exp == 0);
        /* Increase the number of digits up to 6 */
        count += count < 6;
        /* Re-evaluate scientific notation including rollovers to 10^-6 */
        sci = exp > 5 || -6 >= exp;
    }

    /* Find significant digits */
    int digits[6] = {0};
    int d;
    for (d = count - 1; d >= 0; d--) {
        digits[d] = norm_int % 10;
        norm_int /= 10;
    }

    /* Write zeros or digits before decimal point */
    d = 0;
    do {
        *destination++ = '0' + digits[d] * !zeros;
        d += !zeros;
        zeros -= zeros > 0;
    }
    while (!sci && d <= exp);

    /* Place decimal if significant digits remain */
    if (d < count)
        *destination++ = '.';

    /* Write zeros or digits after decimal point */
    while (d < count) {
        *destination++ = '0' + digits[d] * !zeros;
        d += !zeros;
        zeros -= zeros > 0;
    }

    *destination = '\0';
    if (sci) {
        *destination++ = 'e';
        IecStringDecimal(destination, size - 9, exp, 0, ' ');
    }

    return 0;
}
