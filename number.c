/*******************************************************************************
File: IecString\number.c
Author: Tyler Matijevich
Date: 2022-01-06
*******************************************************************************/
 
#include <IecString.h>
#include <stdint.h>
#include <string.h>

static int32_t powerOfTen(uint8_t power);
static uint8_t countDigits(int32_t number);
static char digitToChar(uint8_t digit);

/* Pad an integer with zeros or spaces. Returns destination */
uint32_t IecStringNumber(char *destination, int32_t number, uint8_t width, uint8_t mode, uint32_t size) {
	
	/* Declare local variables */
	char pad = mode ? ' ' : '0';
	uint8_t numberOfDigits = countDigits(number);
	uint8_t maxDigits, digit;
	uint8_t i, offset = number < 0 ? 1 : 0;
	
	/* Verify parameters */
	if(destination == NULL || size == 0) return (uint32_t)destination;
	
	/* Verify length */
	width = (width > 10 ? 10 : width); /* Saturate to 10 */
	maxDigits = (width > numberOfDigits ? width : numberOfDigits);
	if(maxDigits + offset > size - 1) return (uint32_t)destination;
	
	/* Negative exception */
	if(number == INT32_MIN) {
		IecStringCopy(destination, "-2147483648", size);
		return (uint32_t)destination;
	}
	
	/* Accommodate sign */
	if(offset) {
		destination[0] = '-';
		number = -number;
	}
	
	/* Pad */
	for(i = 0; i < maxDigits; i++) {
		digit = maxDigits - i;
		if(digit > numberOfDigits)
			destination[offset + i] = pad;
		else if(digit == 10)
			destination[offset + i] = digitToChar(number / powerOfTen(digit - 1));
		else
			destination[offset + i] = digitToChar((number % powerOfTen(digit)) / powerOfTen(digit - 1));
	}
	
	destination[offset + i] = '\0';
	return (uint32_t)destination;
 	
} /* End function */

/* Return power of ten up to the ninth power (10 characters) */
int32_t powerOfTen(uint8_t power) {
	switch(power) {
		case 0: return 1;
		case 1: return 10;
		case 2: return 100;
		case 3: return 1000;
		case 4: return 10000;
		case 5: return 100000;
		case 6: return 1000000;
		case 7: return 10000000;
		case 8: return 100000000;
		default: return 1000000000;
	}
}

/* Count number of digits in a 32-bit integer */
uint8_t countDigits(int32_t number) {
	uint8_t i;
	for(i = 10; i > 1; i--) {
		if(number / powerOfTen(i - 1)) /* Round down integer division */
			return i;
	}
	return 1;
}

/* Return character of a single digit (0-9) */
char digitToChar(uint8_t digit) {
	switch(digit) {
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		default: return '0'; /* Zero or out-of-range */
	}
}
