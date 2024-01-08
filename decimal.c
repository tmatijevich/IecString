/*******************************************************************************
 * File: decimal.c
 * Created: 2022-09-20
 * 
 * Authors: 
 *   Tyler Matijevich
 * 
 * License:
 *   This file decimal.c is part of the IecString project 
 *   released under the MIT license agreement.
 ******************************************************************************/

#ifndef IECSTRING_STANDALONE
#include <IecString.h>
#else
#include "type.h"
#endif

#include <stdint.h>
#include <string.h>

#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

/* Maximum of 12 bytes: 10 digits, 1 sign, and null terminator */
#define MAX_BYTE 12U
#define MAX_WIDTH 11U
#define MAX_DIGIT 10U

int32_t IecStringDecimal(char *destination, uint32_t size, int32_t value, 
                        uint8_t width, unsigned char pad) {

    /* Gaurd null pointers */
    if (!destination)
        return IECSTRING_ERROR_NULL;

    /* Signed exception */
    if (value == INT32_MIN) {
        /* Do not truncate if whole number cannot fit */
        if (size < MAX_BYTE) return IECSTRING_ERROR_SIZE;
        strcpy(destination, "-2147483648");
        return 0;
    }

    /* Find sign and magnitude */
    unsigned int is_signed = value < 0 ? 1 : 0;
    value = is_signed ? -value : value;

    /* Find digits */
    unsigned int num_digits = 0;
    unsigned int digits[MAX_DIGIT];
    do {
        digits[num_digits++] = value % 10;
        value /= 10;
    }
    while (value);

    /* Saturate width */
    /* num_digits + is_signed <= width <= MAX_WIDTH*/
    width = MIN(MAX(num_digits + is_signed, width), MAX_WIDTH);
    if (size < width + 1) return IECSTRING_ERROR_SIZE;

    /* Write sign */
    if (is_signed)
        *destination++ = '-';

    /* Write pads */
    /* ' ' <= pad <= '~' */
    pad = MIN(MAX(' ', pad), '~');
    while (width - num_digits - is_signed) {
        *destination++ = pad;
        width--;
    }

    /* Write digits */
    while (num_digits) 
        *destination++ = '0' + digits[--num_digits];

    /* Add null terminator */
    *destination = '\0';

    return 0;
}
