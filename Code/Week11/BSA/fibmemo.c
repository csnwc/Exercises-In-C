#include "bsa.h"

#define MAXFIB 35

int fib_memo(bsa* b, int n);

// Use memoisation to speed-up recursive Fibonacci
int main(void)
{
   test();
   bsa* b = bsa_init();
   bsa_set(b,1, 1);
   bsa_set(b,2, 1);

   for(int i=1; i<=MAXFIB; i++){
      printf("%d => %d\n", i, fib_memo(b, i));
   }

   bsa_free(b);
   return 0;
}

int fib_memo(bsa* b, int n)
{
   if(n < 1){
      return 0;
   }
   int* p = bsa_get(b, n);
   if(p){
      return *p;
   }
   return fib_memo(b, n-1) + fib_memo(b, n-2);
}
