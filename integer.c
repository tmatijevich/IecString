/*******************************************************************************
 * File: integer.c
 * Created: 2022-09-20
 * 
 * Authors: 
 *   Tyler Matijevich
 * 
 * License:
 *   This file integer.c is part of the IecString project 
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

/* Maximum of 12 bytes: 10 digits, 1 sign, and null terminator */
#define MAX_BYTE 12U
#define MAX_WIDTH 11U
#define MAX_DIGIT 10U

int32_t IecStringInteger(char *destination, uint32_t size, int32_t value, 
                        uint8_t width, unsigned char pad) {
    
    /* Local variables */
    char temp_string[MAX_BYTE];
    uint8_t i = 0, num_digit = 0;
    int32_t temp_value;

    /* Verify parameters */
    if (destination == NULL)
        return IECSTRING_ERROR_NULL;

    /* Signed exception */
    if (value == INT32_MIN) {
        /* Do not truncate if whole number cannot fit */
        if (size < MAX_BYTE) return IECSTRING_ERROR_SIZE;
        strcpy(destination, "-2147483648");
        return 0;
    }

    /* Write sign */
    if (value < 0) {
        temp_string[i++] = '-';
        value *= -1;
    }
    
    /* Find number of digits */
    temp_value = value;
    do {
        temp_value /= 10;
        num_digit++;
    }
    while (temp_value);

    /* Saturate width */
    /* num_digit + i <= width <= MAX_WIDTH*/
    width = MIN(MAX(num_digit + i, width), MAX_WIDTH);
    if (size < width + 1) return IECSTRING_ERROR_SIZE;

    /* Write pads */
    /* ' ' <= pad <= '~' */
    pad = MIN(MAX(' ', pad), '~');
    while (width - num_digit - i)
        temp_string[i++] = pad;

    /* Write digits */
    i = 0;
    while (num_digit - i) {
        temp_string[width - i - 1] = value % 10 + '0';
        value /= 10;
        i++;
    }

    /* Complete temp string, and copy */
    temp_string[width] = '\0';
    strcpy(destination, temp_string);
    return 0;
}
