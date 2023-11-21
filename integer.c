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

/* Maximum of 10 digits for a 32 bit integer */
#define DIGIT_MAX 10U
/* Maximum of 12 characters (10 digits, 1 sign, and null terminator) */
#define CHAR_MAX 12U

/* Prototypes */
int64_t PowTen(uint8_t exponent);
uint8_t GetWidth(int32_t value);
char GetChar(uint8_t value);

int32_t IecStringInteger(char *destination, uint32_t size, int32_t value, 
                        uint8_t width, uint8_t spaces) {
    
    /* Local variables */
    char pad = spaces ? ' ' : '0';
    char text[CHAR_MAX];
    uint8_t i, offset = 0, char_width, value_width;

    /* Signed exception */
    if (value == INT32_MIN) {
        /* Do not truncate if whole number cannot fit */
        if (size < CHAR_MAX)
            return IECSTRING_ERROR_SIZE;
        else
            return IecStringCopy(destination, size, "-2147483648");
    }

    /* Saturate width */
    value_width = GetWidth(value);
    char_width = MIN(MAX(width, value_width), DIGIT_MAX);

    /* Signed */
    if (value < 0) {
        text[offset++] = '-';
        value = -value;
    }

    /* Write text */
    for (i = char_width; i > 0; i--) {
        if (i > value_width)
            text[offset++] = pad;
        else
            text[offset++] = GetChar((value % PowTen(i)) / PowTen(i - 1));
    }

    /* Add null terminator and check size */
    text[offset++] = '\0';
    if (size < offset)
        return IECSTRING_ERROR_SIZE;
    else
        return IecStringCopy(destination, size, text);
}

/* Powers of ten */
int64_t PowTen(uint8_t exponent) {
	switch (exponent) {
		case 0: return 1LL;
		case 1: return 10LL;
		case 2: return 100LL;
		case 3: return 1000LL;
		case 4: return 10000LL;
		case 5: return 100000LL;
		case 6: return 1000000LL;
		case 7: return 10000000LL;
		case 8: return 100000000LL;
		case 9: return 1000000000LL;
		default: return 10000000000LL;
	}
}

/* Character width of integer */
uint8_t GetWidth(int32_t value) {
	uint8_t i;
	/* Check widths from 10 to 2, default to 1 */
	for (i = DIGIT_MAX; i > 1; i--) {
		if (value / PowTen(i - 1))
			break;
	}
	return i;
}

/* Digit character */
char GetChar(uint8_t value) {
	switch(value) {
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		default: return '0';
	}
}
