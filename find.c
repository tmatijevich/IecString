/*******************************************************************************
 * File: find.c
 * Created: 2024-03-23
 *
 * Authors:
 *   Tyler Matijevich
 *
 * License:
 *   This file find.c is part of the IecString project
 *   released under the MIT license agreement.
 ******************************************************************************/

#include "main.h"

uint32_t IecStringFind(char *source, char *find)
{
    return (uint32_t)strstr(source, find);
}
