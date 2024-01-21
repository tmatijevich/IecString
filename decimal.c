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

#include <IecString.h>
#include <stdint.h>
#include <string.h>

#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

/* Maximum of 12 bytes: 10 digits, 1 sign, and null terminator */
#define MAX_BYTE 12U
#define MAX_WIDTH 11U
#define MAX_DIGIT 10U

int32_t IecStringDecimal(char *destination, uint32_t size, int32_t value,
                         uint8_t width, unsigned char flags) {

    /* Gaurd null pointers */
    if (!destination)
        return IECSTRING_ERROR_NULL;

    /* Check for zero size */
    if (!size)
        return IECSTRING_ERROR_SIZE_ZERO;

    /* Signed exception */
    if (value == INT32_MIN) {
        if (size < MAX_BYTE) {
            /* Clear destination */
            *destination = '\0';
            return IECSTRING_ERROR_SIZE_INVALID;
        }
        strcpy(destination, "-2147483648");
        return 0;
    }

    /* Find sign and magnitude */
    unsigned int is_signed = value < 0 ? 1 : 0;
    unsigned int sign = flags & IECSTRING_FLAG_SIGN || is_signed ? 1 : 0;
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
    /* num_digits + sign <= width <= MAX_WIDTH*/
    width = MIN(MAX(num_digits + sign, width), MAX_DIGIT + sign);
    if (size <= width) {
        /* Clear destination */
        *destination = '\0';
        return IECSTRING_ERROR_SIZE_INVALID;
    }

    /* Write sign */
    if (sign)
        *destination++ = is_signed ? '-' : '+';

    /* Write pads */
    char pad = flags & IECSTRING_FLAG_SPACES ? ' ' : '0';
    while (width - num_digits - sign) {
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
