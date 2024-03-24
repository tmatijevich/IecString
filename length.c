/*******************************************************************************
 * File: length.c
 * Created: 2024-03-23
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file length.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

/* Determine the length of a string */
uint32_t IecStringLength(char *source)
{
    /* Guard null pointers */
    if (!source)
        return 0;

    return (uint32_t)strlen(source);
}
