
/* Boolean(Bit) Array/Vector
   Little-endian: LSB  */

#pragma once 

#include "../../ADTs/General/general.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef enum logicalop {or, and, xor} logicalop;

/* All elements initialised to "0" */
boolarr* boolarr_init(void);

/* Create boolarr based on string e.g. "1100001" */
boolarr* boolarr_initstr(const char* str);

/* Return a deep copy */
boolarr* boolarr_clone(const boolarr* ba);

/* Get number of bits in array */
unsigned int boolarr_size(const boolarr* ba);

/* Return number of bits that are set true */
unsigned int boolarr_count1s(const boolarr* ba);

/* Set nth bit on/off */
bool boolarr_set(boolarr* ba, const unsigned int n, const bool b);
/* Get nth bit */
bool boolarr_get(const boolarr* ba, const unsigned int n, bool* b);

/* Return if two arrays are the same (bitwise) */
bool boolarr_issame(const boolarr* b1, const boolarr* b2);

/* Store to string - rightmost bit is LSB */
bool boolarr_tostring(const boolarr* ba, char* str);

/* Print out array & meta info */
bool boolarr_print(const boolarr* ba);

/* Flip all bits */
bool boolarr_negate(boolarr* ba);

/* Functions dealing with 2 bitwise-arrays */
/* Must be the same length */
boolarr* boolarr_bitwise(const boolarr* ba1, const boolarr* ba2, const logicalop l);

/* Clears all space */
bool boolarr_free(boolarr* p);
