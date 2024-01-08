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

    /* Write sign */
    char temp[MAX_BYTE];
    unsigned int i = 0;
    if (value < 0) {
        temp[i++] = '-';
        value *= -1;
    }
    
    /* Find number of digits */
    int32_t norm_val = value;
    unsigned int num_digit = 0;
    do {
        norm_val /= 10;
        num_digit++;
    }
    while (norm_val);

    /* Saturate width */
    /* num_digit + i <= width <= MAX_WIDTH*/
    width = MIN(MAX(num_digit + i, width), MAX_WIDTH);
    if (size < width + 1) return IECSTRING_ERROR_SIZE;

    /* Write pads */
    /* ' ' <= pad <= '~' */
    pad = MIN(MAX(' ', pad), '~');
    while (width - num_digit - i)
        temp[i++] = pad;

    /* Write digits */
    i = 0;
    while (num_digit - i) {
        temp[width - i - 1] = value % 10 + '0';
        value /= 10;
        i++;
    }

    /* Complete temp string, and copy */
    temp[width] = '\0';
    strcpy(destination, temp);
    return 0;
}
