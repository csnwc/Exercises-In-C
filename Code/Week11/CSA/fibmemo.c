#include "csa.h"

#define MAXFIB 40

int fib_memo(csa* c, int n);

// Use memoisation to speed-up *recursive* Fibonacci
int main(void)
{
   csa* c = csa_init();
   csa_set(c,1, 1);
   csa_set(c,2, 1);

   for(int i=1; i<=MAXFIB; i++){
      printf("%d => %d\n", i, fib_memo(c, i));
   }

   csa_free(&c);
   return 0;
}

int fib_memo(csa* c, int n)
{
   if(n < 1){
      return 0;
   }
   int i;
   // Previously stored
   if(csa_get(c, n, &i)){
      return i;
   }
   // Create from scratch
   int ans = fib_memo(c, n-1) + fib_memo(c, n-2);
   assert(csa_set(c,n,ans));
   return ans;
}
