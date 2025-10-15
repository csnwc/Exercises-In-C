#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

enum validchars {outofbounds='\0', unknown=' ', grass='.', tent='+', tree='*', sep='|'};
typedef enum validchars validchars;

struct board{
   // Tent Count Across the top / per Column
   unsigned short tents_col[BSIZE];
   // The field, square
   char f[BSIZE][BSIZE];
   // Tent Count Down the side / per Row
   unsigned short tents_row[BSIZE];
};
typedef struct board board;

void test(void);
bool inputboard(char* s, char* top, char* side, board* p);
bool solve(board* p);
bool board2str(board b, char* s);
