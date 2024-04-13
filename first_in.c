/*******************************************************************************
 * File: first_in.c
 * Created: 2024-04-03
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file first_in.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

/* First occurrence in source of any character from find */
uint32_t IecStringFirstIn(char *source, char *find)
{
    /* Guard null pointers */
    if (!source || !find)
        /* Return null address */
        return 0;

    /* Returns a pointer to the first occurrence in source of 
       any characters from find */
    return (uint32_t)strpbrk(source, find);
}
