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

/* Convert floating point number to string */
int32_t IecStringFloat(char *destination, uint32_t size, float value) {
    
    /* Local variables */
    uint8_t digits[6] = {0};
    float norm_val;
    int32_t norm_int;
    int8_t exp, i;
    IecStringFormatType values;

    /* Write sign */
    strcpy(values.s[0], "+");
    if (value < 0.0) {
        value *= -1.0f;
        strcpy(values.s[0], "-");
    }

    /* Derive exponent */
    norm_val = value;
    exp = 0;
    while (norm_val) {
        if (norm_val >= 10.0f) {
            norm_val /= 10.0f;
            exp++;
            continue;
        }
        if (norm_val < 1.0f) {
            norm_val *= 10.0f;
            exp--;
            continue;
        }
        break;
    }

    /* Derive normalized value */
    norm_val = value;
    i = 5 - exp;
    while (i) {
        if (i > 0) {
            norm_val *= 10.0f;
            i--;
            continue;
        }
        if (i < 0) {
            norm_val /= 10.0f;
            i++;
            continue;
        }
        break;
    }
    norm_int = (int32_t)(norm_val + 0.5);
    if (norm_int >= 1000000) {
        norm_int /= 10;
        exp++;
    }

    /* Derive significant digits */
    for (i = 5; i >= 0; i--) {
        digits[i] = norm_int % 10;
        values.i[i] = digits[i];
        norm_int /= 10;
    }

    values.f[0] = exp;
    IecStringFormat(destination, size, 
                    "sign: %s, significant digits: %i%i%i%i%i%i, "
                    "exponent: %f", &values);

    return 0;
}
