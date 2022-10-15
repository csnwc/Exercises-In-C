#include "bingrid.h"

#define BOARDSTR (MAX*MAX+1)

int main(void)
{

   test();

   board b;
   char str[BOARDSTR];

   // String Invalid
   assert(str2board(&b, "")==false);

   // Not an even size x even size board
   assert(str2board(&b, "...1.0...")==false);

   // An empty board still gives a 'sensible' string
   b.sz = 0;
   board2str(str, &b);
   assert(strcmp(str, "")==0);
   
   // Solvable 2x2 Board
   assert(str2board(&b, ".0.."));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "1001")==0);

   // Solvable 4x4 Board
   assert(str2board(&b, "...1.0......1..1"));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "0101101001101001")==0);

   // Solvable4x4 Board
   assert(str2board(&b, "....0.0....1..0."));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "1010010100111100")==0);

   // Unsolvable 4x4 Board
   assert(str2board(&b, "...1.0.........1"));
   assert(solve_board(&b)==false);

   // Solvable 6x6 Board
   assert(str2board(&b, "1...1...0.....00...1................"));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "101010100101010011011010101100010101")==0);

   // Unsolvable 6x6 Board
   assert(str2board(&b, "....0...1.....11...0................"));
   assert(solve_board(&b)==false);

   // Solvable 8x8 Board
   assert(str2board(&b, "0.............0.00...1.....00.......0.....0..1.......00........."));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "0101011010011001001011010110011010010011110011000110100110110010")==0);

   return 0;
}
