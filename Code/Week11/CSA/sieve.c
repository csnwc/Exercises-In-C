// Needs both the csa_foreach() and
// the csa_delete() extensions
#include "csa.h"

#define MAX 271

void print(int* p, int* n);
int next_factor(csa* b, int p);

// Compute prime numbers following method of:
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// https://oeis.org/A000959
int main(void)
{
   csa* b = csa_init();
   for(int i=2; i<=MAX; i++){
      assert(csa_set(b,i,i));
   }
   int p = 1;
   while(p<=MAX){
      p = next_factor(b, p);
      for(int i=2*p; i<=MAX; i+=p){
         csa_delete(b, i);
      }
   }
   csa_foreach(print, b, &p);
   csa_free(&b);
   return 0;
   
}

int next_factor(csa* b, int p)
{
   p++;
   int n;
   for(int i=p; i<=MAX; i++){
      if(csa_get(b,i,&n)){
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
