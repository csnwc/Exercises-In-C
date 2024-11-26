#include "ext.h"

#define MAXSTR 50

int main(void)
{

   test();

   dict* d = NULL;
   char str[MAXSTR];

/* !!!!!!!!!!!!!!!!!!!!*/
/* The basic functions */

   // No words are in empty DS
   assert(dict_spell(d, "the")==NULL);
   // No nodes in empty tree
   assert(dict_wordcount(NULL)==0);

/* The figure in the assignment  */
   d = dict_init();
   assert(dict_addword(d, "car"));
   assert(dict_addword(d, "cart"));
   assert(dict_addword(d, "part"));
   assert(dict_wordcount(d)==3);
   assert(dict_mostcommon(d)==1);
   dict_free(&d);

/* A slightly different example */
   d = dict_init();
   // Should be a non-NULL address
   assert(d);
   assert(dict_wordcount(d)==0);
   // Can't add a NULL string
   assert(dict_spell(d, NULL)==NULL);

   // 'car' isn't in the DS
   assert(dict_spell(d, "car")==NULL);
   // So add it
   assert(dict_addword(d, "car"));
   // It's there now
   assert(dict_spell(d, "car"));
   // Top node + 'c' + 'a' + 'r'
   assert(dict_wordcount(d)==1);

   // carted isn't in there
   assert(dict_spell(d, "carted")==NULL);
   // Put it in
   assert(dict_addword(d, "carted"));
   // It is now
   assert(dict_spell(d, "carted"));
   assert(dict_wordcount(d)==2);

   // Cart isn't there as a terminal word
   assert(dict_spell(d, "cart")==NULL);
   // Put it in (case-insensitive)
   assert(dict_addword(d, "Cart"));
   // It's now there
   assert(dict_spell(d, "cart"));
   assert(dict_wordcount(d)==3);

   // Cart'd isn't there as a terminal word
   assert(dict_spell(d, "cart'd")==NULL);
   // Put it in
   assert(dict_addword(d, "cart'd"));
   // It's now there
   assert(dict_spell(d, "Cart'd"));
   // New nodes were created
   assert(dict_wordcount(d)==4);

   // Only one of each word at the moment
   assert(dict_mostcommon(d)==1);
   // Increments the freq variable
   // Should return false (but not checked)
   dict_addword(d, "cart");
   // Now 'cart' has been added twice 
   assert(dict_mostcommon(d)==2);
   // Fifth word
   assert(dict_wordcount(d)==5);

   // Pointer to the bottom of cart...
   dict* p = dict_spell(d, "cart");
   assert(p);

   // Add some new words
   dict_addword(d, "par");
   dict_addword(d, "part");
   dict_addword(d, "parted");
   dict_addword(d, "parter");
   // 5 car prefixed + 4 par prefixed
   assert(dict_wordcount(d)==9);
   dict_free(&d);
   assert(d==NULL);

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* Basic functions, but lots of data from file */

   #define DICTFILES 3
   // unique words : wordle has no apostrophes
   // but english_65197 does
   // Lots of repeated words : p-and-p-words
   char dictnames[DICTFILES][MAXSTR] = {"wordle.txt", "english_65197.txt", "p-and-p-words.txt"};
   int mostc[DICTFILES] = {1, 1, 4331};
   dict* dcts[DICTFILES];
   for(int i=0; i<DICTFILES; i++){
      d = dict_init();
      dcts[i] = d; // Keep dictionaries for later
      assert(d);
      // Word count
      int wc = 0;
      FILE* fp = fopen(dictnames[i], "rt");
      if(!fp){
         fprintf(stderr, "Cannot open word file?\n");
         exit(EXIT_FAILURE);
      }
      while(fgets(str, MAXSTR, fp) != NULL){
         char str2[MAXSTR];
         sscanf(str, "%s", str2);
         // If unique word file, it's not inserted yet ...
         if(mostc[i] == 1){
            assert(dict_spell(d, str2)==NULL);
         }
         //printf(">%s<\n", str2);
         dict_addword(d, str2);
         wc++;
         // ... but it is now
         assert(dict_spell(d, str2));
      }
      fclose(fp);
      assert(dict_mostcommon(d)==mostc[i]);
      assert(dict_wordcount(d)==wc);
   }

   // Free up all those dictionaries
   for(int i=0; i<DICTFILES; i++){
      dict_free(&dcts[i]);
   }

   return 0;
}
