#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#define MSKLEN 64
typedef uint64_t mask_t;

struct block {
   // realloc-style array
   int* vals;
   mask_t msk;
   unsigned int offset;
};
typedef struct block block;

struct csa {
   // realloc-style array
   block* b;
   int n;
};
typedef struct csa csa;

csa* csa_init(void);

// Adds a new index/value, or overwrites
// the value if the index already exists.
// Returns true, unless c is NULL.
bool csa_set(csa* c, int idx, int val);

// If cell has already been written, sets *n = csa[idx] & returns true.
// If any of the pointers is NULL, or if the cell is unset, returns false.
bool csa_get(csa* c, int idx, int* n);

// Produces a stringified version of the CSA (see driver.c)
void csa_tostring(csa* c, char* s);

// Deletes an array entry - returns
// false if it was never set anyway,
// true if it was.
bool csa_delete(csa* c, int idx);

// Call func() for every valid value of array.
// func() pass a pointer to the stored integer value.
void csa_foreach(void (*func)(int* p, int* acc), csa* c, int* ac);

// Usage : csa_free(&c)
// Frees up all space pointed to by c, then sets c to be NULL
void csa_free(csa** l);

void test(void);
