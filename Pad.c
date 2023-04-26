/*******************************************************************************
 * File: IecString\Overlap.c
 * Author: Tyler Matijevich
 * Date: 2022-09-20
 ******************************************************************************/

#include "Main.h"

#define DIGIT_MAX 10;
#define INT_CHAR_MAX DIGIT_MAX + 1 + 1;

static int64_t PowTen(uint8_t Exponent);
static uint8_t GetWidth(int32_t Value);
static char GetDigitChar(uint8_t Digit);

/* Pad integer with zeroes or spaces */
int32_t IecStringPad(char *Destination, uint32_t Size, int32_t Value, uint8_t Width, uint8_t Space) {
	
	/* Local variables */
	char Pad = Space ? ' ' : '0';
	char Text[INT_CHAR_MAX];
	uint8_t i, Offset = 0;
	
	/* Exception */
	if(Value == INT32_MIN) {
		if(Size < INT_CHAR_MAX)
			return IECSTRING_ERROR_LENGTH;
		else
			return IecStringCopy(Destination, Size, "-2147483648");
	}
	
	/* Saturate width */
	Width = MIN(MAX(Width, GetWidth(Value)), DIGIT_MAX);
	
	/* Signed */
	if(Value < 0) {
		Text[Offset++] = '-';
		Value = -Value;
	}
	
	/* Write text */
	for(i = Width; i > 0; i--) {
		if(i > GetWidth(Value))
			Text[Offset++] = Pad;
		else
			Text[Offset++] = GetDigitChar((Value % PowTen(i)) / PowTen(i - 1));
	}
	
	Text[Offset++] = '\0';
	if(Size < Offset)
		return IECSTRING_ERROR_LENGTH;
	else
		return IecStringCopy(Destination, Size, Text);
}

/* Powers of ten */
int64_t PowTen(uint8_t Exponent) {
	switch(Exponent) {
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
uint8_t GetWidth(int32_t Value) {
	uint8_t i;
	/* Check widths from 10 to 2, default to 1 */
	for(i = DIGIT_MAX; i > 1; i--) {
		if(Value / PowTen(i - 1))
			break;
	}
	return i;
}

/* Digit character */
char GetDigitChar(uint8_t Digit) {
	switch(Digit) {
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
