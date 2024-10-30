#include "mydefs.h"

#define MAXSTR (BRDSZ*BRDSZ+BRDSZ+2)

int main(void)
{

   test();

   // size - > max Board  tiles + hyphens + hawk 
   char str[MAXSTR];
   state* s;

   //assert(file2str("2moves.brd", str));
   strcpy(str, "A-ABC-ABC-ABC-CBA");
   s = str2state(str);
   assert(s);
   assert(solve(s, true)==2);
   free(s);

   assert(file2str("0moves.brd", str));
   assert(strcmp("A-B", str)==0);
   s = str2state(str);
   assert(s);
   assert(solve(s, false)==0);
   free(s);

   assert(file2str("4moves.txt", str));
   assert(strcmp("O-COMS-COMS-COMS-CMMS-CSSO", str)==0);
   s = str2state(str);
   assert(s);
   assert(solve(s, false)==4);
   free(s);

   assert(file2str("imposs.brd", str));
   assert(strcmp("A-BC-DE", str)==0);
   s = str2state(str);
   assert(solve(s, false)==-1);
   free(s);

   assert(file2str("10moves.brd", str));
   s = str2state(str);
   assert(solve(s, false)==10);
   free(s);

   assert(file2str("9moves.brd", str));
   s = str2state(str);
   assert(solve(s, false)==9);
   free(s);

   assert(file2str("11moves.brd", str));
   s = str2state(str);
   assert(solve(s, false)==11);
   free(s);

   assert(file2str("imposs.brd", str));
   assert(strcmp("A-BC-DE", str)==0);
   s = str2state(str);
   assert(solve(s, false)==-1);
   free(s);

   return EXIT_SUCCESS;
}
