/*******************************************************************************
 * File: length_in.c
 * Created: 2024-04-12
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file length_in.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

/* Initial length in source containing only characters from find */
uint32_t IecStringLengthIn(char *source, char *find)
{
    /* Guard null pointers */
    if (!source || !find)
        /* Return zero length */
        return 0;

    return (uint32_t)strspn(source, find);
}
