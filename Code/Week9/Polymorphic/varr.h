#pragma once

#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
A resizeable. variable-type indexed array ADT. Here:
1. Setting an element out of bounds reallocs the array to make it valid.
2. Getting an element out-of-bounds is an error.
3. An element that is in-bounds, but has never been set, may contain undefined values.
3. arr_get returns a void* to a block of memory - the size of each element is specified on initialisation.
*/

typedef struct arr arr;

/* Creates the empty array */
arr* arr_init(int elementsize);
/* Similar to l[n] = i, safely resizing if required */
/* data from v is copied and stored into array */
void arr_set(arr *l, int n, void* v);
/* Similar to = l[n] */
/* pointer into array is returned */
void* arr_get(arr *l, int n);
/* Clears all space used, and sets pointer to NULL */
void arr_free(arr **l);
