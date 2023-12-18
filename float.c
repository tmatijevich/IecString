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

#include "main.h"

/* Prototypes */
int8_t GetFloatExponent(float value, int8_t exponent);
float Pow10(int8_t exponent, float value);

/* Convert floating point number to string */
int32_t IecStringFloat(char *destination, uint32_t size, float value) {
    
    /* Local variables */
    char sig_digits[7] = {0};
    float temp;
    int8_t exponent, i;
    IecStringFormatType values;

    /* Write sign */
    if (value < 0.0) {
        temp = -value;
        strcpy(values.s[0], "-");
    }
    else {
        temp = value;
        strcpy(values.s[0], "+");
    }

    /* Write significant digits */
    exponent = GetFloatExponent(value, 0);
    temp *= Pow10(5 - exponent, 1.0);
	temp += 0.5;
    for (i = 5; i >= 0; i--) {
        sig_digits[i] = (int32_t)(temp) % 10 + '0';
        temp /= 10.0;
    }
    strcpy(values.s[1], sig_digits);

    values.i[0] = exponent;

    IecStringFormat(destination, size, 
                    "sign: %s, significant digits: %s, exponent: %i", &values);

    return 0;
}

int8_t GetFloatExponent(float value, int8_t exponent) {
    if (value == 0.0) return 0;
    if (value < 0.0) value *= -1.0;
    if (value >= 10.0) {
        value /= 10.0;
        return GetFloatExponent(value, ++exponent);
    }
    if (value < 1.0) {
        value *= 10.0;
        return GetFloatExponent(value, --exponent);
    }
    return exponent;
}

float Pow10(int8_t exponent, float value) {
    if (exponent > 0)
        return Pow10(--exponent, value * 10.0);
    if (exponent < 0)
        return Pow10(++exponent, value / 10.0);
    return value;
}
