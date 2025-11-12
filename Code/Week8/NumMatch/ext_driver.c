#include "ext_nm.h"

int main(void)
{
   //test();
   board b = randfill(6);
   // 18866
   // 62725
   // 32795
   // 34448

   // 8 8 Horiz
   assert(take(&b,  (pair){1,0,2,0}));
   // 2 2 Vertical 
   assert(take(&b,  (pair){1,1,1,2}));
   // 3 7 Horiz across gap
   assert(take(&b,  (pair){0,2,2,2}));
   // 6 7 Fails
   assert(!take(&b, (pair){3,0,2,1}));

   // Lets do it all again, but positions reversed
   b = randfill(6);
   assert(take(&b,  (pair){2,0,1,0}));
   assert(take(&b,  (pair){1,2,1,1}));
   assert(take(&b,  (pair){2,2,0,2}));
   assert(!take(&b, (pair){2,1,3,0}));

   // Some More
   b = randfill(6);
   assert(take(&b,  (pair){1,0,2,0}));
   assert(!take(&b, (pair){0,0,3,2}));

   b = randfill(15);
   // 37499
   // 45428
   // 58362
   // 79892
   assert(take(&b,  (pair){2,1,3,2}));
   assert(!take(&b, (pair){1,2,4,2}));

   // Which boards are solvable
   assert( solve(3648));
   assert( solve(1762));
   assert( solve( 924));
   assert( solve( 363));
   // Or not
   assert(!solve(   6));
   assert(!solve(2000));
   assert(!solve( 666));

   return EXIT_SUCCESS;
}
