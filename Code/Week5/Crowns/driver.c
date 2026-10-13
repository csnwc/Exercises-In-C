#include "crowns.h"

int main(void)
{
   // Test all your (sub-)functions here
   test();

   char str[2*MXBSIZE*MXBSIZE];
   board b;

   // Incorrectly formed boards
   assert(str2board(&b, "")==false);
   assert(str2board(&b, "a a |b ")==false);
   // If either of the arguments are NULL, return false
   assert(board2str(str, NULL)==false);
   // 4 x 4, one crown already set, all rest unknown, regions a..d
   assert(str2board(&b, "a a b*b |a a a b |a c c b |d d c c "));
   assert(b.sze == 4);
   assert(count_unknowns(b) == 15);
   assert(board2str(str, &b));
   assert(strcmp(str,   "a a b*b |a a a b |a c c b |d d c c ")==0);

   // RULE1 TEST
   // Put in crosses due to 1 crown already placed, true if any changes
   assert(rule1(&b));
   // No additional changes can be made?
   assert(!rule1(&b));
   assert(count_unknowns(b)==6);
   assert(board2str(str, &b));
   assert(strcmp(str, "aXaXb*bX|a aXaXbX|a c cXbX|d d cXc ")==0);


   // RULE2 TESTS
   // Three Crowns already found
   assert(str2board(&b, "w*wXwXmXmX|wXwXwXm m |wXg*gXmXmX|wXgXeXeXb |wXgXe*eXbX"));
   assert(b.sze == 5);
   assert(count_unknowns(b)==3);
   assert(rule2(&b));
   // All changes been made, so no new rule2 'nove' possible
   assert(!rule2(&b));
   assert(board2str(str, &b));
   assert(strcmp(str,   "w*wXwXmXmX|wXwXwXm*mX|wXg*gXmXmX|wXgXeXeXb*|wXgXe*eXbX")==0);

   assert(str2board(&b, "G W W W WX|G G W W WX|G G E W WX|G M EXEXB |GXM M EXB "));
   assert(count_unknowns(b)==18);
   assert(rule2(&b));
   assert(board2str(str, &b));
   assert(strcmp(str,   "GXWXWXW*WX|G*GXWXWXWX|GXGXE*WXWX|GXMXEXEXB*|GXM*MXEXBX")==0);


   // RULE3 TEST
   // 5 x 5, regions b, e, g, l, w
   assert(str2board(&b, "b b e e e |b b b e e |b w b e e |b w b l l |b g g l l "));
   assert(b.sze == 5);
   // Regions 'w' and 'e' lead to many cross insertions using rule 3.
   rule3(&b);
   assert(board2str(str, &b));
   assert(strcmp(str,  "b bXeXeXeX|bXbXbXe eX|bXw bXeXeX|bXwXbXlXl |bXgXg lXlX")==0);
   // 5 unknowns left must be crowns
   assert(count_unknowns(b)==5);
   // Rule2 will mop all these up
   assert(rule2(&b));
   assert(count_unknowns(b)==0);


   // RULE5 TEST
   // Solvabl 5x5
   assert(str2board(&b, "m m g g g |m m m g g |m w m g g |m w m b b |m e e b b "));
   assert(b.sze == 5);
   assert(rule5(&b));
   assert(count_unknowns(b)==0);
   // Solvable 6x6
   assert(str2board(&b, "k k g g g g |k k g m g g |k k g m g g |e e g m b b |e e g m b b |e e g m w w "));
   assert(b.sze == 6);
   assert(rule5(&b));
   assert(count_unknowns(b)==0);
   // Solvable 8x8
   assert(str2board(&b, "m m m m m m m m |m b b b b m m m |m c b b b g m m |m c c c c g m m |m c c k c g g w |m m c k c g g w |m m k k c c s s |m m m m o o s s "));
   assert(b.sze == 8);
   assert(rule5(&b));
   assert(count_unknowns(b)==0);
   assert(board2str(str, &b));
   assert(strcmp(str, "m*mXmXmXmXmXmXmX|mXbXb*bXbXmXmXmX|mXcXbXbXbXg*mXmX|mXc*cXcXcXgXmXmX|mXcXcXkXcXgXgXw*|mXmXcXk*cXgXgXwX|mXmXkXkXcXcXs*sX|mXmXmXmXo*oXsXsX")==0);

   return EXIT_SUCCESS;
}
