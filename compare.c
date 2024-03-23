/*******************************************************************************
 * File: compare.c
 * Created: 2024-03-23
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file compare.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

int16_t IecStringCompare(char *string1, char *string2, uint32_t characters)
{
    return strncmp(string1, string2, characters);
}
