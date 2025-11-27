#include "csa.h"

#define BIGSTR 100000

void sum(int* p, int* ac);
void gap(int* p, int* ac);
void dblit(int* p, int* ac);

int main(void)
{

   csa* c = NULL;
   char str[BIGSTR];
   int n = 1;

   test();

   // Empty CSA
   csa_tostring(c, str);
   assert(strcmp(str, "")==0);
   c = csa_init();
   assert(!csa_get(c, 0, &n));
   assert(!csa_get(c, 2, &n));
   // First Add (csa[2]=25)
   assert(csa_set(c, 2,  25));
   // Add csa[3]=30
   assert(csa_set(c, 3,  30));
   // Add csa[63]=100
   assert(csa_set(c, 63, 100));

   // Getters
   assert(csa_get(c,  2, &n));
   assert(n==25);
   assert(csa_get(c,  3, &n));
   assert(n==30);
   assert(csa_get(c, 63, &n));
   assert(n==100);
   csa_tostring(c, str);
   assert(strcmp(str, "1 block {3|[2]=25:[3]=30:[63]=100}")==0);

   // Use one whole block: csa[i]=i*10
   for(int i=0; i<64; i++){
      assert(csa_set(c, i,  i*10));
      assert(csa_get(c, i, &n));
      assert(n==i*10);
   }
   // Clean Up
   csa_free(&c);
   assert(c==NULL);

   //Let's do it all again, but with +200 higher indices
   c = csa_init();
   csa_tostring(c, str);
   assert(strcmp(str, "0 blocks")==0);
   assert(csa_set(c, 202,  25));
   assert(csa_set(c, 203,  30));
   assert(csa_set(c, 263, 100));
   assert(csa_get(c, 202, &n));
   assert(n==25);
   assert(csa_get(c, 203,  &n));
   assert(n==30);
   assert(csa_get(c, 263, &n));
   assert(n==100);
   csa_tostring(c, str);
   // 2 blocks, the first has 2 entries csa[202]=25 & csa[203]=30, and the 2nd
   // has 1 entry csa[263]=100
   assert(strcmp(str, "2 blocks {2|[202]=25:[203]=30}{1|[263]=100}")==0);
   csa_free(&c);
   assert(c==NULL);

#ifdef EXT
   // EXTENSION : foreach
   c = csa_init();
   int accumulator = 0;
   assert(csa_set(c,  5, 10));
   assert(csa_set(c, 50, 20));
   csa_foreach(sum, c, &accumulator);
   assert(accumulator==30);

   // For this structure csa[50] will be stored in the adjacent cell
   // to csa[5], therefore one int apart.
   csa_foreach(gap, c, &accumulator);
   assert(accumulator==1);

   assert(csa_set(c, 65, 30));
   accumulator = 0;
   csa_foreach(sum, c, &accumulator);
   assert(accumulator==60);
   csa_foreach(dblit, c, &accumulator);
   csa_tostring(c, str);
   assert(strcmp(str, "2 blocks {2|[5]=20:[50]=40}{1|[65]=60}")==0);
   // For this structure csa[65] will not be stored in the adjacent cell
   // to csa[50], therefore not one int apart.
   csa_foreach(gap, c, &accumulator);
   assert(accumulator!=1);

   // EXTENSION : delete
   assert(!csa_delete(c,  1));
   assert( csa_delete(c, 50));
   csa_tostring(c, str);
   assert(strcmp(str, "2 blocks {1|[5]=20}{1|[65]=60}")==0);
   assert(csa_delete(c, 5));
   csa_tostring(c, str);
   assert(strcmp(str, "1 block {1|[65]=60}")==0);
   assert(csa_delete(c, 65));
   csa_tostring(c, str);
   assert(strcmp(str, "0 blocks"));
   // Don't need to do full csa_free() - only the
   // csa structure itself should be in use by now ...
   free(c);
#endif
   return EXIT_SUCCESS;
}

// p  : gets passed a pointer to each array value address in turn.
// ac : Pointer to an accumulator to store intermediate results
void sum(int* p, int* ac)
{
   *ac += *p;
}

void dblit(int* p, int* ac)
{
   // void variable not used warning
   *ac = 0;
   // integer stored in array is doubled
   *p *= 2;
}

void gap(int* p, int* ac)
{
   static int* prv = NULL;
   // The 'gap' between this pointer & last one
   // May the coding Gods forgive me ;-(
   *ac = (int)(p - prv);
   prv = p;
}
