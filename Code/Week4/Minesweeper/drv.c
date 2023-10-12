#include "ms.h"

int main(void)
{
   driver();
   test();
   return 0;
}

// Code so you can check your code gives the correct output
void driver(void)
{
   board b;
   char str[MAXSQ*MAXSQ+1];

   // syntax_check checks whether character count is correct & contains valid characters etc.
   // but NOT whether the board has been numbered correctly etc.

   // Invalid string (too small)
   strcpy(str, "11?010?");
   assert(syntax_check(1, 5, 5, str)==false);

   // Invalid string (has an 'l' not a '1')
   strcpy(str, "11?0?X111l111X?11?11?X10?");
   assert(syntax_check(3, 5, 5, str)==false);

   // No unknowns
   strcpy(str, "000000111001X100111000000");
   assert(syntax_check(1, 5, 5, str)==true);
   b = make_board(1, 5, 5, str);
   board2str(str, b);
   assert(strcmp(str, "000000111001X100111000000")==0);

   // No unknowns
   strcpy(str, "XXXXXX535XX303XX535XXXXXX");
   assert(syntax_check(16, 5, 5, str)==true);
   b = make_board(16, 5, 5, str);
   board2str(str, b);
   assert(strcmp(str, "XXXXXX535XX303XX535XXXXXX")==0);

   // 1X1 mine
   strcpy(str, "X");
   assert(syntax_check(1, 1, 1, str)==true);
   b = make_board(1, 1, 1, str);
   b = solve_board(b);
   board2str(str, b);
   assert(strcmp(str, "X")==0);
  
   // Rule 1 : 3x3 with 8 mines, 1 unknown
   strcpy(str, "XXXX?XXXX");
   assert(syntax_check(8, 3, 3, str)==true);
   b = make_board(8, 3, 3, str);
   b = solve_board(b);
   board2str(str, b);
   assert(strcmp(str, "XXXX8XXXX")==0);
 
   // Rule 1 : 5x5 with 3 mines, multiple unknowns
   strcpy(str, "11?0?X1111111X?11?11?X10?");
   assert(syntax_check(3, 5, 5, str)==true);
   b = make_board(3, 5, 5, str);
   b = solve_board(b);
   board2str(str, b);
   assert(strcmp(str, "11000X1111111X1112111X100")==0);

   // Rules 1&2 : 5x5 with 3 mines, multiple unknowns
   strcpy(str, "?110?1?2101?X?1012?1?0111");
   assert(syntax_check(3, 5, 5, str)==true);
   b = make_board(3, 5, 5, str);
   b = solve_board(b);
   board2str(str, b);
   assert(strcmp(str, "111001X21012X21012X100111")==0);

}
