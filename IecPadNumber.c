/*********************************************************************************
 * File:      IecPadNumber.c
 * Author:    Tyler Matijevich
 * Created:   January 6, 2022/1:12 PM 
 *********************************************************************************
 * Description: Pad 32-bit signed integers with zeros or spaces to string output
 ********************************************************************************/ 
 
#include <IecString.h>
#include <limits.h>
#include <string.h>

/* Function prototypes */
long TenPow(unsigned char digit);
unsigned char CountDigits(long num);
char DigitChar(unsigned char digit);

/* Pad a whole number with zeros or spaces (up to 10 digits). Return address to string. */
unsigned long IecPadNumber(long num, char *str, unsigned char digits, unsigned char spaces) {
	
	/* Declare local variables */
	char pad = (spaces ? ' ' : '0');	
	unsigned char numDigits = CountDigits(num);
	unsigned char maxDigits, curDigit;
	unsigned char i = 0, offset = (num < 0 ? 1 : 0);
	
	/* Handle max negative exception */
	if(num == LONG_MIN) {
		strcpy(str, "-2147483648");
		return (unsigned long)str;
	}
	
	/* Accommodate sign, then use positive numbers */
	if(offset) {
		str[0] = '-';
		num = -num;
	}
	
	digits = (digits > 10 ? 10 : digits); /* Saturate to 10 digits for 32-bit numbers */
	maxDigits = (digits > numDigits ? digits : numDigits);
	
	for(i = 0; i < maxDigits; i++) {
		curDigit = maxDigits - i;
		if(curDigit > numDigits)
			str[offset + i] = pad;
		else if(curDigit == 10)
			str[offset + i] = DigitChar(num / TenPow(curDigit - 1));
		else
			str[offset + i] = DigitChar((num % TenPow(curDigit)) / TenPow(curDigit - 1));
	}
	
	str[offset + i] = '\0';
	return (unsigned long)str;
 	
} /* Function defintion */

/* Return ten to the power of digit, up to 10 digits (32-bits) */
long TenPow(unsigned char power) {
	
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
		default: return 1000000000; /* Maximum is 10 digits or power of 9 */
	}
	
} 

/* Determine number of digits in a 32-bit integer */
unsigned char CountDigits(long num) {
	
	unsigned char i;
	for(i = 10; i > 1; i--) {
		if(num / TenPow(i - 1)) /* Integer division rounds down */
			return i;
	}
	return 1;
	
} 

/* Get the character for a single digit */
char DigitChar(unsigned char digit) {
	
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
