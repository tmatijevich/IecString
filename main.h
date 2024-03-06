/*******************************************************************************
 * File: main.h
 * Created: 2022-09-20
 * 
 * Authors: 
 *   Tyler Matijevich
 * 
 * License:
 *   This file main.h is part of the IecString project 
 *   released under the MIT license agreement.
 ******************************************************************************/

#ifndef IECSTRING_MAIN_H
#define IECSTRING_MAIN_H

/* Headers */
#ifndef IECSTRING_HEADER_EXPLICIT
#include <IecString.h>
#else
#include <astime.h>
#endif
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* Constants */
#ifdef IECSTRING_HEADER_EXPLICIT
#define IECSTRING_ERROR_NONE 0
#define IECSTRING_ERROR_NULL (-515898392)
#define IECSTRING_ERROR_SIZE_ZERO (-515897392)
#define IECSTRING_ERROR_SIZE_INVALID (-515897382)
#define IECSTRING_ERROR_OVERLAP (-515896392)
#define IECSTRING_WARNING_TRUNCATE (-1589637216)
#define IECSTRING_FLAG_NONE 0U
#define IECSTRING_FLAG_SIGN 1U
#define IECSTRING_FLAG_SPACES 2U
#define IECSTRING_FLAG_E_NOTATION 4U
#endif

/* Macros */
#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

/* Types */
#ifdef IECSTRING_HEADER_EXPLICIT
#ifndef IECSTRING_FORMAT_TYPE_EXTERNAL
#define IECSTRING_FORMAT_INDEX 5U
typedef struct IecStringFormatType
{
    uint8_t b[6];
    double f[6];
    int32_t i[6];
    char s[6][81];
} IecStringFormatType;
#else
#include "../format.h"
#endif
#endif

/* Prototypes */
#ifdef IECSTRING_HEADER_EXPLICIT
int32_t IecStringCopy(char *destination, uint32_t size, char *source);
int32_t IecStringConcat(char *destination, uint32_t size, char *source);
int32_t IecStringReplace(char *destination, uint32_t size, char *source,
                         char *find, char *replace);
int32_t IecStringFormat(char *destination, uint32_t size, char *source, 
                        IecStringFormatType *values);
int32_t IecStringDecimal(char *destination, uint32_t size, 
                         signed long value, unsigned char width, 
                         unsigned char flags);
int32_t IecStringFloat(char *destination, uint32_t size, float value,
                       unsigned char width, unsigned char precision,
                       unsigned char flags);
int32_t IecStringDateTime(char *destination, uint32_t size, 
                          DTStructure *value, char *format);
#endif

#endif /* IECSTRING_MAIN_H */
