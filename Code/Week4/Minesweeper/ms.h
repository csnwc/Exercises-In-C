// Do NOT change this file 

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXSQ 10
typedef struct board {
   int grid[MAXSQ][MAXSQ];
   int w;
   int h;
   int totmines;
} board;

#define UNK  '?'
#define MINE 'X'

// Some driver functions to run your code with - during the marking process
// these will be changed to other, similar, 'tests'.
void driver(void);

// Returns a board based on the minecout, width, height and grid (passed as a string)
board make_board(int minecount, int width, int height, char inp[MAXSQ*MAXSQ+1]);

// Returns string correspnding to the boards grid
void board2str(char s[MAXSQ*MAXSQ+1], board b);

// Repeatedly applies both rules to replace unknows and returns final board
board solve_board(board b);

// Make sure number of characters in string == width*height
// Ensure only characters are from the set:   0123456789?X
// Ensure mines in string <= totmines
bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]);

// To test any other functions you've created in ms.c
void test(void);
