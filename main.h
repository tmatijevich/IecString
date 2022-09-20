/*******************************************************************************
 * File: IecString\main.h
 * Author: Tyler Matijevich
 * Created: 2022-09-20
 ******************************************************************************/

#ifndef IECSTRING_MAIN_H
#define IECSTRING_MAIN_H

#ifdef __cplusplus
extern "C" 
{
#endif

/* Headers */
#include <IecString.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/* Prototypes */
uint8_t overlap(char *destination, uint32_t size, char *source);

#ifdef __cplusplus
};
#endif

#endif /* IECSTRING_MAIN_H */
