/*******************************************************************************
 * File: end.c
 * Created: 2024-03-23
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file end.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

/* Does source end with suffix */
uint8_t IecStringEndsWith(char *source, char *suffix)
{
    /* Guard null pointers */
    if (!source || !suffix)
        return false;

    /* Check lengths */
    size_t source_length = strlen(source);
    size_t suffix_length = strlen(suffix);
    if (suffix_length > source_length)
        return false;

    /* Compare characters of strings */
    return strncmp(source + source_length - suffix_length, 
                   suffix, suffix_length) == 0;
}
