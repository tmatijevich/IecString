/*******************************************************************************
 * File: main.h
 * Created: 2022-09-20
 * 
 * Contributors: 
 * - Tyler Matijevich
 * 
 * License:
 *  This file main.h is part of the IecString project released under the
 *  GNU General Public License v3.0 agreement.  For more information, please 
 *  visit https://github.com/tmatijevich/IecString/blob/main/LICENSE.
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

/* Prototypes */
uint8_t Overlap(char *Destination, uint32_t Size, char *Source);

#endif /* IECSTRING_MAIN_H */
