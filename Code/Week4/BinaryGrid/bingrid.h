#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>

// Maximum grid is 16x16
#define MAX  16
#define UNK  '.'
#define ONE  '1'
#define ZERO '0'

// Our main structure contains a fixed-size array - we'll genrally only use part of it
struct board {
   char b2d[MAX][MAX];
   int sz;
};
typedef struct board board;

// You'll proably have many other functions that need testing
void test(void);

// Given an input string, complete information for board
bool str2board(board* b, char* str);
// Given a board structure, create string version
void board2str(char* str, board* brd);
// Given a board, apply all rules repatedly - return true if solved, false otherwise
bool solve_board(board* brd);
