#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define BIGSTR 1000
#define GRID 100

struct crossword{
   char arr[GRID][GRID];
   int sz;
};
typedef struct crossword crossword;

/*
For your own testing - you'll probably have many auxiliary/sub-functions
inside crossword.c that you'll want to test ... 
*/
void test(void);

/*
   Convert a size (sz) & string (ip) into a crossword*
   White squares are ' ' or '.', black squares 'X' or '*'
*/
bool str2crossword(int sz, char* ip, crossword* cw);

// Convert crossword to string of across & down numbers
void getcluestring(const crossword* c, char* str);

// Get percentage of empty squares that are shared between two clues
int getchecked(crossword c);
