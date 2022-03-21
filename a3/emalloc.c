/** @file emalloc.c
 *  @brief Implementation of emalloc.h
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "emalloc.h"

/**
 * Function:  emalloc
 * --------------------
 * @brief Represents a wrapper to malloc to use it in a safer way.
 *
 * @param size_t The size of the object to reserve dynamic memory for.
 *
 * @return: Void.
 *
 */

void *emalloc(size_t n)
{
    void *p = NULL;

    p = malloc(n);
    if (p == NULL)
    {
        fprintf(stderr, "malloc of %zu bytes failed", n);
        exit(1);
    }

    return p;
}