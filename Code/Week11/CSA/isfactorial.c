// Needs the csa_foreach() extension
#include "csa.h"

void storefactorial(csa* b, int f);
void printfacts(int* p, int* n);

// Store the factorials in a CSA for later use
// https://oeis.org/A000142/list
int main(void)
{
   test();
   int i;
   csa* b = csa_init();
   for(i=0; i<500000000; i++){
      storefactorial(b, i);
   }

   // ...
   // Sometime later, look-up factorials
   printf("Printing all factorials\n");
   csa_foreach(printfacts, b, &i);
   csa_free(&b);
   return 0;
}

void storefactorial(csa* b, int f)
{
   if(f<2){
      csa_set(b, 1, 1);
      return;
   }
   int n = 2;
   int tf = f;
   do{
      if(tf%n!=0){
         return;
      }
      tf/=n;
      n++;
   }while(tf>1); 
   csa_set(b, f, f);
   return;
}

void printfacts(int* p, int* n)
{
   *n = 0;
   printf("%d\n", *p);
}
