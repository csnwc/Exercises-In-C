#include "yy.h"

int main(void)
{

   test();
   grid g;


   assert(readGrid(&g, "./g1_3x3.yy"));
   assert(solutions(&g)==1);
   assert(strcmp(stringify(&g), "+++\nOO+\n+++")==0);

   assert(readGrid(&g, "./g1_4x4.yy"));
   assert(solutions(&g)==1);
   assert(strcmp(stringify(&g), "OOOO\n+++O\n+OOO\n++++")==0);

   assert(readGrid(&g, "./g1_5x5.yy"));
   assert(solutions(&g)==1);
   assert(strcmp(stringify(&g), "+++++\nOOOO+\nO++++\nOOOO+\n+++++")==0);

   assert(readGrid(&g, "./g2_7x7.yy"));
   assert(solutions(&g)==1);
   assert(strcmp(stringify(&g), "+OOOOOO\n+O+++++\n+O+OOO+\n+O+O+O+\n+O+++O+\n+OOOOO+\n+++++++")==0);

   assert(readGrid(&g, "./g2_6x6.yy"));
   assert(solutions(&g)==1);
   assert(strcmp(stringify(&g), "++++++\nOOOOO+\nO+++++\nO+OO+O\nO++O+O\nOOOOOO")==0);

   assert(readGrid(&g, "./g1_7x7.yy"));
   assert(solutions(&g)==1);

   ///// Odd cases

   // 3 solutions ?
   assert(readGrid(&g, "./g1_6x6_nonunique.yy"));
   assert(solutions(&g)==3);

   // 2x2 blank grid has many solutions
   assert(readGrid(&g, "./g1_2x2_nonunique.yy"));
   assert(solutions(&g)==12);
   
   // 4x4 Blank Grid has 96 solutions (I think :-) )
   assert(readGrid(&g, "./g2_4x4_nonunique.yy"));
   assert(solutions(&g)==96);

   // No solution possible due to:
   // +O
   // O+
   assert(readGrid(&g, "./g2_3x3_bad.yy"));
   assert(solutions(&g)==0);

   return EXIT_SUCCESS;

}
