#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Maximum grid size
#define MAXG 10

#define UNK '.'
#define BLK '+'
#define WHT 'O'

struct grid{
   // The square grid
   char m[MAXG][MAXG];
   // Actual size of grid being used.
   // Slightly wasteful to store this in
   // *every* grid, but keeps it simple.
   unsigned short sz;
};
typedef struct grid grid;

/* Your function for testing all your code, including
   sub-functions you write
*/
void test(void);

/* s is the path to a valid file.  
returns false on error e.g. file can't be read.
*/
bool readGrid(grid* g, const char* s);


/* 
   Returns the stringified version of the grid,
   or a NULL point if b is invalid etc.
*/
char* stringify(const grid* g);

/*
   Solve the grid, return number of possible
   solutions (generally == 1), but could be
   higher if an ill-posed starting grid is
   provided, or zero if no solutions possible.
*/
int solutions(grid* g);
