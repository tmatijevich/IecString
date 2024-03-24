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

/* Compare characters of two strings */
int16_t IecStringCompare(char *string1, char *string2, uint32_t characters)
{
    /* Guard null pointers */
    if (!string1 || !string2)
        return string1 ? 1 : -1;

    return strncmp(string1, string2, characters);
}
