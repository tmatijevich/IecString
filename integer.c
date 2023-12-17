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

/* Prototypes */
uint8_t NumberOfDigits(uint32_t value, uint8_t count);

int32_t IecStringInteger(char *destination, uint32_t size, int32_t value, 
                        uint8_t width, unsigned char pad) {
    
    /* Local variables */
    char temp[MAX_BYTE];
    uint8_t i = 0, num_digit;

    /* Verify parameters */
    if (destination == NULL)
        return IECSTRING_ERROR_NULL;

    /* Signed exception */
    if (value == INT32_MIN) {
        /* Do not truncate if whole number cannot fit */
        if (size < MAX_BYTE) return IECSTRING_ERROR_SIZE;
        
        FastCopy(destination, size, "-2147483648");
        return 0;
    }

    /* Write sign */
    if (value < 0) {
        temp[i++] = '-';
        value *= -1;
    }

    /* Saturate width */
    num_digit = NumberOfDigits(value, 0);
    if (width > MAX_WIDTH) width = MAX_WIDTH;
    else if (width < num_digit + i) width = num_digit + i;

    /* Write pads */
    if (pad < ' ') pad = ' ';
    else if (pad > '~') pad = '~';
    while (width - num_digit - i)
        temp[i++] = pad;

    /* Write digits */
    i = 0;
    while (num_digit - i) {
        temp[width - i - 1] = value % 10 + '0';
        value /= 10;
        i++;
    }

    /* Add null terminator and check size */
    temp[width] = '\0';
    if (size < width + 1) return IECSTRING_ERROR_SIZE;

    FastCopy(destination, size, temp);
    return 0;
}

/* Number of digits in an integer */
uint8_t NumberOfDigits(uint32_t value, uint8_t count) {
    value /= 10;
    if (value)
        return NumberOfDigits(value, ++count);
    else
        return ++count;
}
