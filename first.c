/*******************************************************************************
 * File: first.c
 * Created: 2024-04-03
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file first.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

/* Find first occurrence of character in source */
uint32_t IecStringFirst(char *source, uint8_t character)
{
    /* Guard null pointers */
    if (!source)
        return 0;

    /* Returns a pointer to the first occurrence of character in source */
    return (uint32_t)strchr(source, character);
}
