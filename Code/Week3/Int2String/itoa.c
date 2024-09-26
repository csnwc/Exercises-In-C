#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#define BIGSTR 1000

void int2string(int i, char* str);

int main(void)
{
   char s[BIGSTR];

   int2string(0, s);
   assert(strcmp(s, "0")==0);
   int2string(10, s);
   assert(strcmp(s, "10")==0);
   int2string(99, s);
   assert(strcmp(s, "99")==0);
   int2string(124, s);
   assert(strcmp(s, "124")==0);
   int2string(3141, s);
   assert(strcmp(s, "3141")==0);
   int2string(-1000, s);
   assert(strcmp(s, "-1000")==0);
   return 0;
}
