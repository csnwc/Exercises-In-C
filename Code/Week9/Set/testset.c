#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "set.h"

int main(void)
{
   int i;
   set *sa, *sb, *sc, *su, *si;
   int aa[] = {5,1,7,5};
   int ab[] = {4,2,6,7};

   printf("Basic Set Tests ... Start\n");

   /* Check basic set NULL (empty) operations are dealt with correctly */
   assert(set_size(NULL)==0);
   set_remove(NULL,18);
   set_insert(NULL, 1);
   set_free(NULL);
   assert(set_contains(NULL,0)==0);
   /* Check 2 set NULL (empty) operations are dealt with correctly */
   sa = set_fromarray(NULL, 0);
   assert(sa != NULL);
   assert(set_size(sa) == 0);
   sb = set_copy(sa);
   assert(sb != NULL);
   assert(set_size(sb) == 0);
   set_free(&sa);
   set_free(&sb);
   sa = set_fromarray(ab,4);
   assert(set_size(sa)==4);
   sc = set_intersection(NULL,sa);
   assert(sc != NULL);
   assert(set_size(sc)==0);
   sb = set_intersection(sa,NULL);
   assert(sb != NULL);
   assert(set_size(sb)==0);
   set_free(&sa);
   set_free(&sb);
   set_free(&sc);
   sa = set_fromarray(ab,4);
   sc = set_union(NULL,sa);
   assert(set_size(sc)==4);
   sb = set_union(sa,NULL);
   assert(set_size(sb)==4);
   set_free(&sa);
   set_free(&sb);
   set_free(&sc);
   sa = set_union(NULL, NULL);
   assert(sa != NULL);
   assert(set_size(sa)==0);
   set_free(&sa);

   /* Remove */
   sa = set_fromarray(ab,4);
   for(i=0; i<4; i++){
      set_removeone(sa);
      assert(set_size(sa)==3-i);
   }
   set_free(&sa);
   
   /* Basic Set creation */
   sa = set_fromarray(aa,4);
   assert(set_size(sa)==3);
   sb = set_fromarray(ab,4);
   assert(set_size(sb)==4);
   assert(set_contains(sa,1)==1);
   assert(set_contains(sb,1)==0);
   assert(set_contains(sa,5)==1);
   assert(set_contains(sb,5)==0);
   assert(set_contains(sa,7)==1);
   assert(set_contains(sb,7)==1);

   /* Union */
   su = set_union(sa, sb);
   assert(set_size(su)==6);
   assert(set_contains(su,1)==1);
   assert(set_contains(su,2)==1);

   /* Intersections */
   si = set_intersection(sa, sb);
   assert(set_contains(si,7)==1);
   assert(set_contains(si,5)==0);
   assert(set_size(si)==1);

   /* Copying */
   sc = set_copy(sa);
   assert(set_size(sa)==set_size(sc));
   for(i=0; i<set_size(sc); i++){
      assert(set_contains(sa, set_removeone(sc)));
   }

   /* Clear */
   set_free(&sa);
   assert(sa == NULL);
   set_free(&sb);
   assert(sb == NULL);
   set_free(&sc);
   assert(sc == NULL);
   set_free(&si);
   assert(si == NULL);
   set_free(&su);
   assert(su == NULL);
   printf("Basic Set Tests ... Stop\n");

   return 0;
}
