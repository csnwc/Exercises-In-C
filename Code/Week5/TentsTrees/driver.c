#include "tentstrees.h"

int main(void)
{
   test();


   // We only compile these lines if BSIZE has been #defined to be 6
   #if BSIZE == 6
      char s[BSIZE*(BSIZE+1)];
      board b;
      // FAIL : Empty string
      assert(inputboard("", "111111", "222222", &b) ==false);
      // String too long (extra unknown on 5th line)
      assert(inputboard("*    *|    * |      |  *  *|       | **   ","120121", "201112", &b)==false);
      // Invalid square ('N')
      assert(inputboard("*    *|    * |  N   |  *  *|      | **   ", "120121", "201112", &b)==false);
      // Only unknown or tent squares allowed on input, not grass
      assert(inputboard("*    *|    * | ...  |  *  *|      | **   ", "120121", "201112", &b)==false);
      // Total tens per row (6), not same as per column (7)
      assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201111", &b)==false);

      // Solvable
      assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201112", &b)==true);
      assert(solve(&b)==true);
      assert(board2str(b,s));
      assert(strcmp("*+..+*|....*.|....+.|.+*..*|.....+|+**+..", s)==0);

   
      // Solvable
      assert(inputboard(" *    |   *  |     *|      |**    |   ** ", "121111", "111103", &b)==true);
      assert(solve(&b)==true);
      assert(board2str(b,s));
      assert(strcmp(".*.+..|.+.*..|....+*|.+....|**....|+.+**+", s)==0);

      // Solvable
      assert(inputboard("   *  |  **  | *    |      |*    *| *    ", "121111", "111202", &b)==true);
      assert(solve(&b)==true);
      assert(board2str(b,s));
      assert(strcmp("...*+.|.+**..|.*.+..|.+...+|*....*|+*+...", s)==0);
   
      // NOT Solvable
      assert(inputboard("    * |  *   |   *  | *   *|  *   |*     ", "112012", "111121", &b)==true);
      assert(solve(&b)==false);
      assert(board2str(b,s));
      assert(strcmp(".. .* |. *. .|.  *  | * . *|  *.. |*  ...", s)==0);
   #endif

   #if BSIZE == 4
      char s[BSIZE*(BSIZE+1)];
      board b;
      assert(inputboard("*  *|    |*   |   *", "1111", "1102", &b)==true);
      assert(solve(&b)==true);
      assert(board2str(b,s));
      assert(strcmp("*+.*|...+|*...|+.+*", s)==0);
   #endif
   return EXIT_SUCCESS;
}
