/*******************************************************************************
 * File: start.c
 * Created: 2024-03-23
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file start.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

uint8_t IecStringStartsWith(char *source, char *prefix)
{
    /* Guard null pointers */
    if (!source || !prefix)
        return false;

    /* Compare characters of strings */
    return strncmp(source, prefix, strlen(prefix)) == 0;
}
