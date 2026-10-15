#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Maximum board size
#define MXBSIZE 10

enum validmarks {unknown=' ', cross='X', crown='*'};
typedef enum validmarks validmarks;

struct cell{
   // Every cell has a region (e.g. a letter)
   unsigned char region;
   // And a mark - cross, crown etc.
   validmarks mark;
};
typedef struct cell cell;

struct board{
   // The square board
   cell cs[MXBSIZE][MXBSIZE];
   // Actual size of board being used
   unsigned short sze;
};
typedef struct board board;

/* Your function for testing all your code, including
   sub-functions you write
*/
void test(void);

/* s is a string defining the board, two characters per cell.
   The first is the region character, and the second is how
   this cell is marked either ' ' for unknown, 'X' for crossed
   and '*' for crown. 
*/
bool str2board(board* b, char* s);

/* Given a board b, write the 'stringified' version of it
   into str. If str or b are NULL, return false, true otherwise.
*/
bool board2str(char* str, const board* b);

/* For a given board count the number of unknowns
   (i.e. cells which are not marked as crossed or crowns).
*/
int count_unknowns(board b);


/* Takes a board b and adds all the crosses induced by
   crowns placed in it. Returns true if any changes are
   made, false otherwise.
*/
bool rule1(board* b);

/* Takes a board b and adds adds any crowns due to any
   row, column, or region having only one unknown remaining.
   Repeatedly applies this rule, and then rule one until no
   more changes are possible. Returns true if any changes have
   been made at all, or false otherwise.
*/
bool rule2(board* b);

/* Takes a board b and adds adds crosses to any squares that
   would cause another region to have no squares available for
   crowns. Repeatedly applies this until no more changes are
   possible.  Returns true if any changes have been made at all,
   or false otherwise.
*/
bool rule3(board* b);

/* By compiling with 'lut.o' you get this function which
   returns a string corresponding to the nth legal
   solution to a board of size sz into str.
   The basis of rule5. Returns false when n is too large
   for a particular board size.
*/
bool lut(int sz, int n, char str[]);

/* Compute all possible solutions for board b, using lut()
   Fills b with the solution and returns true if one can
   be found, false otherwise.
*/
bool rule5(board* b);



/*

Rule1: (Crowns -> Crosses) All Crowns will 'X' out their entire respective
row, column, 8-neighbours AND region.
Crown placed in the 'A' region:
                          .AB...
                          .AA...
                          FA*EEE
                          ..A...
                          ..C...
                          ..C...
Blank out row, column, 8-neighbours and all others in 'A' region:
                          .XX...
                          .XXX..
                          XX*XXX
                          .XXX..
                          ..X...
                          ..X...


Rule2: (Singletons) Any row, column OR region with only one unknown
square remaining will have a Crown added to that square.  Apply this rule
(and Rule 1 if appropriate) repeatedly until no changes can be made.

Rule3: (Add Crosses) If putting a crown in a cell of one region (and
therefore the crosses associated with it), would completely cover
another region thus prevent if having a valid crown, this cell needs to
be crossed.  Apply this rule repeatedly until no changes can be made.

Rule5: (Brute Force) Explore all possible legal permutations of crowns,
discounting solutions that don't have exactly one crown per region.

*/
