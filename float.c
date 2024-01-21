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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* Maximum size of output string: <+|->XXXXXX.XXXXXX or <+|->X.XXXXXXe<+|->XX */
#define MAX_BYTE 15
/* Maximum size for special numbers (infinity, zero, not a number) */
#define MAX_BYTE_SPECIAL 5
/* Maximum exponent without scientific notation */
#define MAX_EXP 5
/* Minimum exponent without scientific notation */
#define MIN_EXP (-6)
/* Maximum number of significant digits */
#define MAX_DIGIT 7
/* Exponent of +38 to -38 is four bytes and three characters */
#define EXP_BYTE 4
#define EXP_WIDTH 3

/* Convert float to string */
int32_t IecStringFloat(char *destination, uint32_t size, float value) {
    
    /* Gaurd null pointer */
    if (!destination)
        return IECSTRING_ERROR_NULL;

    /* Check for zero size */
    if (!size)
        return IECSTRING_ERROR_SIZE_ZERO;
    
    /* Check for insufficient size */
    if (size < MAX_BYTE_SPECIAL) {
        /* Clear destination */
        *destination = '\0';
        return IECSTRING_ERROR_SIZE_INVALID;
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

    /* Calculate the base 10 exponent */
    int exp = (int)floorf(log10f(value));

    /* Use scientific notation if large exponent */
    int sci = exp < MIN_EXP || MAX_EXP < exp;

    /* Count the number of significant digits */
    /* Add exponent if exponent is between MIN_EXP and 0 */
    int num_sd = MAX_DIGIT + exp * (MIN_EXP <= exp && exp < 0);

    /* Count leading zeros */
    int leading = MAX_DIGIT - num_sd;

    /* Count trailing zeros */
    int trailing = ((MAX_EXP - MIN_EXP + 1) - MAX_DIGIT - (MAX_EXP - exp)) * 
        (num_sd == MAX_DIGIT && !sci);

    /* Normalize significant digits before the decimal point */
    double norm_val = 1.0;
    for (int i = num_sd - 1 - exp; i != 0; i += i > 0 ? -1 : 1)
        norm_val *= i > 0 ? 10.0 : 0.1;
    norm_val *= value;

    /* Convert normalized value to int with rounding */
    int32_t norm_int = (int32_t)roundf(norm_val);

    /* Calculate the maximum normalized value */
    int32_t norm_max = 1;
    for (int i = 0; i < num_sd; i++)
        norm_max *= 10;
    
    /* Check for rollover after rounding */
    if (norm_int >= norm_max) {
        /* Re-normalize if exceeds max */
        norm_int = num_sd == MAX_DIGIT ? norm_int / 10 : norm_int;
        /* Increase the exponent */
        exp++;
        /* Decrease leading zero count if missing significant digits */
        leading -= leading > 0 && num_sd < MAX_DIGIT;
        /* Increase number of significant digits */
        num_sd += num_sd < MAX_DIGIT;
        /* Re-evaluate scientific notation including rollovers to MIN_EXP */
        sci = exp <= MIN_EXP || MAX_EXP < exp;
    }

    /* Determine the total width */
    int width = sign + leading + num_sd + 1 + trailing + sci * (1 + EXP_WIDTH);
    if (size <= width) {
        /* Clear destination */
        *destination = '\0';
        return IECSTRING_ERROR_SIZE_INVALID;
    }

    /* Calculate significant digits */
    int digits[MAX_DIGIT] = {0};
    int d;
    for (d = num_sd - 1; d >= 0; d--) {
        digits[d] = norm_int % 10;
        norm_int /= 10;
    }

    /* Write leading zeros or significant digits before decimal point */
    d = 0;
    do {
        /* Write digit if no leading zeros remain */
        *destination++ = '0' + digits[d] * !leading;
        /* Update digit count if no leading zeros remain */
        d += !leading;
        /* Update leading zeros */
        leading -= leading > 0;
    }
    while (!sci && d <= exp);

    /* Place decimal */
    *destination++ = '.';

    /* Write zeros or significant digits after decimal point */
    while (d < num_sd || trailing) {
        /* Write digit if no more leading zeros and digits remain */
        *destination++ = '0' + (d < MAX_DIGIT && !leading ? digits[d] : 0);
        /* Update trailing zero count if no digits remain */
        trailing -= d >= MAX_DIGIT;
        /* Update digit count if no leading zeros remain */
        d += !leading;
        /* Update leading zeros */
        leading -= leading > 0;
    }

    *destination = '\0';
    if (sci) {
        *destination++ = 'e';
        IecStringDecimal(destination, EXP_BYTE, exp, EXP_WIDTH,
                         IECSTRING_FLAG_SIGN);
    }

    return 0;
}
