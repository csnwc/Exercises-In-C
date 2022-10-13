#include "crossword.h"

int main(void)
{
   test();
   char str[BIGSTR];
   crossword c;

   // Invalid (string NULL)
   assert(!str2crossword(1, NULL, &c));
   // Invalid (crossword* NULL)
   assert(!str2crossword(2, "", NULL));
   // Invalid (size incorrect)
   assert(!str2crossword(-7, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));
   // Invalid (string too short)
   assert(!str2crossword(7, "", &c));
   // Invalid (string too long)
   assert(!str2crossword(5, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));
   // Invalid (size too large)
   assert(!str2crossword(500, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));

   // Valid Crosswords 
   assert(str2crossword(3, ".........", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-4-5|D-1-2-3", str)==0);
   // All squares are shared (checked)
   assert(getchecked(c)==100);

   // Example from handout
   assert(str2crossword(5, "....X.XX.X.X......X.XX...", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-3-5-6|D-1-2-3-4", str)==0);
   assert(getchecked(c)==53);

   assert(str2crossword(5, "X...X...............X...X", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-4-6-7-8|D-1-2-3-4-5", str)==0);
   assert(getchecked(c)==100);

   // Can be ' ' and '*', not just '.' and 'X'
   assert(str2crossword(5, "*   *               *   *", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-4-6-7-8|D-1-2-3-4-5", str)==0);
   assert(getchecked(c)==100);

   assert(str2crossword(7, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-3-6-8|D-2-4-5-6-7", str)==0);
   assert(getchecked(c)==32);

   assert(str2crossword(7, "X.X........X.XX.X.X.X.......X.X.X.X....X.XX.X....", &c));
   getcluestring(&c, str);
   assert(strcmp("A-2-4-5-6-7|D-1-2-3", str)==0);
   assert(getchecked(c)==33);

   assert(str2crossword(7, "...X....X...X....X...X.XXX.X...X....X...X....X...", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-3-5-6-8-10-12-14-15-16|D-1-2-3-4-7-9-10-11-12-13", str)==0);
   assert(getchecked(c)==67);

   assert(str2crossword(7, "........X.XXX..X......X.X.X......X..XXX.X........", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-4-6-7|D-1-2-3-5", str)==0);
   assert(getchecked(c)==33);

   assert(str2crossword(8, ".....X.XX.X.X..........XX.X.X......X.X.XX..........X.X.XX.X.....", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-5-6-7-8-11-12-13|D-2-3-4-5-9-10", str)==0);
   assert(getchecked(c)==43);

}
