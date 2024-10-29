#include "crushit.h"
#include "mydefs.h"

int main(void)
{

   assert(initialise(NULL, NULL) == false);
   state s;

/*
PPPDP
CDAAC
DAAPD
AAPCA
APCDA
PCAAA
*/
   // Well-formed string
   assert(initialise(&s, "PPPDPCDAACDAAPDAAPCAAPCDAPCAAA") == true);
   char str[WIDTH*MAXROWS+1];
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "PPPDPCDAACDAAPDAAPCAAPCDAPCAAA") == 0);

   assert(initialise(&s, "../../BBBBB.brd") == true);
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "BBBDBCDAACDAABDAABCAABCDABCAAA") == 0);

   return 0;
}
