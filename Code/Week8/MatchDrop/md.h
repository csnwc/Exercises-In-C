#pragma once

/* Converts file definition of starting board
into a string, to make checking etc. easier.
File contains the hawk tile, then each row
of the board in turn per line.
Returned strings is of the form A-ABC-BCA-BAC, each
row is separated by a '-' symbol and the hawk tile
is specified first.
Args : Name of file to open, str to be filled.
Returns: false if any of the 2 pointers are NULL, if
the file can't be opened, or is badly formed;
else returns true.
*/
bool file2str(const char* fname, char* str);

/* Converts string definition of starting board
into the first board of a 'state' structure and
returns it. 
Args : String to be read.
Returns: NULL is there are any problems;
else returns state.
*/
state* str2state(const char* str);


/* For a state s, returns the number of 'moves'
required to solve the board.
An already solved board=0
An impossible board=-1
If verbose==true, then print out the solution,
otherwise, print nothing.
*/
int solve(state* s, bool verbose);

void test(void);
