#include "soll.h"
#include "specific.h"

#define LISTSTRLEN 1000

int main(void)
{
   char str[LISTSTRLEN];
   long cnt = 0;
   printf("Test Self-Org LL (%s) Start ... ", SOLLTYPE);

   assert(soll_free(NULL));
   assert(soll_size(NULL) == 0);
   soll_add(NULL, "1one");

   soll* s = soll_init(none);
   assert(soll_size(s) == 0);
   soll_add(s, "1one");
   assert(soll_isin(s, "1one", &cnt));
   assert(soll_freq(s, "1one")==2);
   assert(soll_size(s) == 1);
   soll_add(s, "2two");
   assert(soll_freq(s, "2two")==1);
   assert(soll_size(s) == 2);
   assert(soll_isin(s, "2two", &cnt));
   assert(soll_freq(s, "2two")==2);
   soll_add(s, "3three");
   assert(soll_size(s) == 3);
   soll_tostring(s, str);
   assert(!strcmp("1one(2)|2two(2)|3three(1)", str));
   assert(soll_remove(s, "2two"));
   assert(soll_size(s) == 2);
   assert(soll_remove(s, "3three"));
   assert(soll_size(s) == 1);
   assert(soll_remove(s, "1one"));
   assert(soll_size(s) == 0);
   assert(soll_free(s));

   s = soll_init(mtf);
   assert(soll_size(s) == 0);
   soll_add(s, "1one");
   assert(soll_size(s) == 1);
   soll_add(s, "2two");
   assert(soll_size(s) == 2);
   assert(soll_isin(s, "1one", &cnt));
   assert(soll_isin(s, "2two", &cnt));
   soll_add(s, "3three");
   assert(soll_size(s) == 3);
   soll_tostring(s, str);
   assert(!strcmp("2two(2)|1one(2)|3three(1)", str));
   assert(soll_remove(s, "2two"));
   assert(soll_size(s) == 2);
   assert(soll_remove(s, "3three"));
   assert(soll_size(s) == 1);
   assert(soll_remove(s, "1one"));
   assert(soll_size(s) == 0);
   assert(soll_free(s));

   s = soll_init(transpose);
   assert(soll_size(s) == 0);
   soll_add(s, "1one");
   assert(soll_size(s) == 1);
   soll_add(s, "2two");
   assert(soll_size(s) == 2);
   assert(soll_isin(s, "1one", &cnt));
   assert(soll_isin(s, "2two", &cnt));
   soll_add(s, "3three");
   assert(soll_size(s) == 3);
   assert(soll_isin(s, "3three", &cnt));
   soll_tostring(s, str);
   assert(!strcmp("2two(2)|3three(2)|1one(2)", str));
   assert(soll_remove(s, "2two"));
   assert(soll_size(s) == 2);
   assert(soll_remove(s, "3three"));
   assert(soll_size(s) == 1);
   assert(soll_remove(s, "1one"));
   assert(soll_size(s) == 0);
   assert(soll_free(s));


   printf("End\n");
   return 0;
}
