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
#include <IecString.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/* Macros */
#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

/* Prototypes */
uint8_t Overlap(char *destination, uint32_t size, char *source);

#endif /* IECSTRING_MAIN_H */
