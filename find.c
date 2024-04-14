/*******************************************************************************
 * File: find.c
 * Created: 2024-04-02
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file find.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

/* Find substring in source */
uint32_t IecStringFind(char *source, char *find)
{
    /* Guard null pointers */
    if (!source || !find)
        return 0;

    /* Returns a pointer to the first occurence of find in source */
    /* Returns a null pointer if find is not in source */
    return (uint32_t)strstr(source, find);
}
