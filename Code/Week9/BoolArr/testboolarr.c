#include "specific.h"
#include "boolarr.h"

#define BIGSTR 1000

int main(void)
{

   bool b;
   char str[BIGSTR];
   boolarr* ba;
   boolarr* bb;
   boolarr* bc;
   unsigned int i;
   bool b2;

   assert(boolarr_size(NULL)==0);
   assert(!boolarr_get(NULL, 0, &b));
   assert(!boolarr_set(NULL, 0, true));
   assert(!boolarr_set(NULL, 1, true));
   assert(boolarr_issame(NULL, NULL));
   assert(!boolarr_tostring(NULL, str));
   assert(boolarr_count1s(NULL)==0);
   ba = boolarr_init();
   assert(!boolarr_issame(NULL, ba));
   assert(!boolarr_issame(ba, NULL));
   assert(boolarr_count1s(ba)==0);
   assert(!boolarr_tostring(ba, NULL));
   assert(boolarr_size(ba)==0);
   assert(boolarr_set(ba, 1, true));
   assert(boolarr_get(ba, 0, &b));
   assert(!b);
   assert(boolarr_set(ba, 5, true));
   assert(boolarr_set(ba, 6, false));
   assert(boolarr_tostring(ba, str));
   assert(strcmp(str, "0100010")==0);

   assert(boolarr_set(ba, 0, true));
   assert(boolarr_set(ba, 127, true));
   assert(boolarr_set(ba, 128, true));
   assert(boolarr_set(ba, 191, true));
   assert(boolarr_set(ba, 194, true));

   assert(boolarr_print(ba));

   assert(boolarr_get(ba,0,&b));
   assert(b);
   assert(boolarr_get(ba,2,&b));
   assert(!b);
   assert(boolarr_get(ba,126,&b));
   assert(!b);
   assert(boolarr_get(ba,127,&b));
   assert(b);
   assert(boolarr_get(ba,128,&b));
   assert(b);
   assert(boolarr_get(ba,191,&b));
   assert(b);
   assert(boolarr_get(ba,194,&b));
   assert(b);

   bc = boolarr_clone(ba);
   assert(boolarr_get(bc,0,&b));
   assert(b);
   assert(boolarr_get(bc,2,&b));
   assert(!b);
   assert(boolarr_get(bc,126,&b));
   assert(!b);
   assert(boolarr_get(bc,127,&b));
   assert(b);
   assert(boolarr_get(bc,128,&b));
   assert(b);
   assert(boolarr_get(bc,191,&b));
   assert(b);

   assert(boolarr_count1s(ba) == boolarr_count1s(bc));

   assert(boolarr_issame(ba, ba));
   assert(boolarr_issame(bc, bc));
   assert(boolarr_issame(ba, bc));
   assert(boolarr_issame(bc, ba));

   assert(boolarr_set(bc, 0, false));
   assert(boolarr_get(bc, 0, &b));
   assert(b==false);
   assert(boolarr_set(bc, 1, false));
   assert(boolarr_get(bc, 1, &b));
   assert(b==false);

   bb = boolarr_clone(ba);
   boolarr_negate(bb);
   for(i=0; i<boolarr_size(ba); i++){
      assert(boolarr_get(ba, i, &b ));
      assert(boolarr_get(bb, i, &b2));
      assert(b != b2);
   }
   boolarr_free(ba);
   boolarr_free(bb);
   boolarr_free(bc);

   /* Bitwise */
   ba = boolarr_initstr("100100100");
   assert(ba);
   bb = boolarr_initstr("110110110");
   assert(bb);

   bc = boolarr_bitwise(ba, bb, and);
   assert(bc);
   assert(boolarr_tostring(bc, str));
   assert(strcmp(str, "100100100")==0);
   assert(boolarr_issame(ba, bc));
   boolarr_free(bc);

   bc = boolarr_bitwise(ba, bb, or);
   assert(bc);
   assert(boolarr_tostring(bc, str));
   assert(strcmp(str, "110110110")==0);
   assert(boolarr_issame(bb, bc));
   boolarr_free(bc);

   bc = boolarr_bitwise(ba, bb, xor);
   assert(bc);
   assert(boolarr_tostring(bc, str));
   assert(strcmp(str, "010010010")==0);

   boolarr_free(ba);
   boolarr_free(bb);
   boolarr_free(bc);

   return 0;
}
