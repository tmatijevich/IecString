/*******************************************************************************
 * File: IecString\Main.h
 * Author: Tyler Matijevich
 * Date: 2022-09-20
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
#include <string.h>

/* Prototypes */
uint8_t Overlap(char *Destination, uint32_t Size, char *Source);

#ifdef __cplusplus
};
#endif

#endif /* IECSTRING_MAIN_H */
