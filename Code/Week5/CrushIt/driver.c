#include "crushit.h"
#include "mydefs.h"

int main(void)
{

   test();

   assert(initialise(NULL, "") == false);
   state s;
   assert(initialise(&s, NULL) == false);
   // Input string too short (not a multiple of 5)
   assert(initialise(&s, "ABCDBCDAACDAABDAABCAABCDABCDA") == false);
   // Incorrect character '+'
   assert(initialise(&s, "ABCDBCDAACDAABDAABCAABCDABCD+A") == false);

/*
BBBDB
CDAAC
DAABD
AABCA
ABCDA
BCAAA
*/
   // Well-formed string
   assert(initialise(&s, "BBBDBCDAACDAABDAABCAABCDABCAAA") == true);
   char str[WIDTH*MAXROWS+1];
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "BBBDBCDAACDAABDAABCAABCDABCAAA") == 0);

   assert(matches(&s) == true);
/*
...DB
CDAAC
DAABD
AABC.
ABCD.
BC...
*/
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "...DBCDAACDAABDAABC.ABCD.BC...") == 0);

   assert(dropblocks(&s) == true);
/*
.....
CD.D.
DAAA.
AAABB
ABBCC
BCCDD
*/
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "CD.D.DAAA.AAABBABBCCBCCDD") == 0 );

/*
.....
CD.D.
D....
...BB
ABBCC
BCCDD
*/
   assert(matches(&s) == true);
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "CD.D.D.......BBABBCCBCCDD") == 0);
   assert(dropblocks(&s) == true);
/*
C..D.
DD.BB
ABBCC
BCCDD
*/
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "C..D.DD.BBABBCCBCCDD") == 0);



   /* File version */
   assert(initialise(&s, "./b1.txt") == true);
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "BBBDBCDAACDAABDAABCAABCDABCAAA") == 0);

   /* Match at 3 (not 4) on left near top of board */
   assert(initialise(&s, "lft.txt") == true);
   assert(matches(&s)==true);
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "ABCDE.BCDE.CDEF.DEFABCDEFCDEFADEFAB") == 0);


   // All of these can be matched on the first pass ...
/*
AAAAA
AAAAA
AAAAA
AAAAA
AAAAA
AAAAA
*/
   assert(initialise(&s, "./a.txt") == true);
   assert(matches(&s)==true);
   assert(dropblocks(&s)==true);
   assert(tostring(&s, str) == true);
   // Board is empty -> empty string ""
   assert(strlen(str) == 0);
   assert(matches(&s)==false);

   /* Some of these3 are 'off' the screen so not matched
      on the first pass */
/*
CCCCC
CCCCC
CCCCC
CCCCC
CCCCC
CCCCC
CCCCC
CCCCC
*/
   assert(initialise(&s, "./c.txt") == true);
   assert(matches(&s)==true);
   assert(dropblocks(&s)==true);
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "CCCCCCCCCC") == 0);

/* Big, complex starting data that you should
   be able to match and drop lots of times ... */
   assert(initialise(&s, "./fourteen.txt") == true);
   // Keep looping while we can make changes.
   for(int i=0; i<14; i++){
      assert(matches(&s));
      assert(dropblocks(&s));
   }
   assert(tostring(&s, str) == true);
   assert(strcmp(str,    "...B...ABEBCCDDAABAE") == 0);

   return 0;
}
