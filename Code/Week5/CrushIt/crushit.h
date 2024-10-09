#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "mydefs.h"

// 'state' is a typedef'd structure which needs 
// to be defined in *your* "mydefs.h" header.

/* Initialises the state of the board etc.
   String contains either a filename (the default),
   but if this cannot be opened is assumed to be
   a representation of the board per row, top-down.
   Fails if string is not a filename and is malformed */
bool initialise(state* s, const char* str);

/* Returns the string corresponding to the board. 
   Only the lower part of the board is returned,
   based on the height of the highest column that
   contains ABCDs in it, this may be more than the
   lowest six rows.
   If s or str are NULL, return false, else
   return true; */
bool tostring(const state* s, char* str);

/* Removes all 3+ long blocks & puts a
   hole in their place.
   Returns false if s is NULL, else returns
   whether any blocks any have been removed. */
bool matches(state* s);
/*
   Fills all holes by dropping blocks (if any)
   from above.
   Returns false if s is NULL, else rearranges
   blocks so that holes are filled by blocks above
   and returns true. */
bool dropblocks(state* s);

/* Your chance to properly test your functions.
   You *won't* be able to properly test file-reading
   though (since you can't make any assumptions about
   which .txt files I do or do not have.) */
void test(void);
