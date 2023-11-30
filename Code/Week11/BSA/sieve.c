#include "bsa.h"

#define MAX 271

void print(int* p, int* n);
int next_factor(bsa* b, int p);

// Compute the prime numbers following method of:
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// https://oeis.org/A000959
int main(void)
{
   test();
   bsa* b = bsa_init();
   for(int i=2; i<=MAX; i++){
      assert(bsa_set(b,i,i));
   }
   int p = 1;
   for(int j=0; p<=MAX; j++){
      p = next_factor(b, p);
      for(int i=2*p; i<=MAX; i+=p){
         bsa_delete(b, i);
      }
   }
   bsa_foreach(print, b, &p);
   return 0;
   
}

int next_factor(bsa* b, int p)
{
   p++;
   for(int i=p; i<=MAX; i++){
      int* q = bsa_get(b,i);
      if(q){
         return i;
      }
   }
   return p;
}

void print(int* p, int* n)
{
   *n = 0;
   printf("%d\n", *p);
}
