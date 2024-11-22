#include "t27.h"

#define MAXSTR 50

int main(void)
{

   test();

   dict* d = NULL;
   char str[MAXSTR];

/* !!!!!!!!!!!!!!!!!!!!*/
/* The basic functions */

   // No words are in empty tree
   assert(dict_spell(d, "the")==NULL);
   // No nodes in empty tree
   assert(dict_nodecount(NULL)==0);
   assert(dict_wordcount(NULL)==0);

/* The figure in the assignment  */
   d = dict_init();
   assert(dict_addword(d, "car"));
   assert(dict_addword(d, "cart"));
   assert(dict_addword(d, "part"));
   assert(dict_nodecount(d)==9);
   assert(dict_wordcount(d)==3);
   assert(dict_mostcommon(d)==1);
   dict* q1 = dict_spell(d, "car");
   dict* q2 = dict_spell(d, "part");
   assert(dict_cmp(q1, q2)==7);
   // It's unsigned
   assert(dict_cmp(q2, q1)==7);
   // 2 steps up from 'carter' is 'cart'
   dict_autocomplete(d, "car", str);
   // Most frequently stored word after car is car+t
   assert(strcmp(str, "t")==0);
   dict_free(&d);

/* A slightly different example */
   d = dict_init();
   // Should be a non-NULL address
   assert(d);
   // Top node always exists
   assert(dict_nodecount(d)==1);
   assert(dict_wordcount(d)==0);
   // Can't add a NULL string
   assert(dict_spell(d, NULL)==NULL);

   // 'car' isn't in the tree
   assert(dict_spell(d, "car")==NULL);
   // So add it
   assert(dict_addword(d, "car"));
   // It's there now
   assert(dict_spell(d, "car"));
   // Top node + 'c' + 'a' + 'r'
   assert(dict_nodecount(d)==4);
   assert(dict_wordcount(d)==1);

   // carted isn't in there
   assert(dict_spell(d, "carted")==NULL);
   // Put it in
   assert(dict_addword(d, "carted"));
   // It is now
   assert(dict_spell(d, "carted"));
   // 'car' -> 'carted' is 3 extra nodes
   assert(dict_nodecount(d)==7);
   assert(dict_wordcount(d)==2);

   // Cart isn't there as a terminal word
   assert(dict_spell(d, "cart")==NULL);
   // Put it in (case-insensitive)
   assert(dict_addword(d, "Cart"));
   // It's now there
   assert(dict_spell(d, "cart"));
   // No new nodes were created
   assert(dict_nodecount(d)==7);
   assert(dict_wordcount(d)==3);

   // Cart'd isn't there as a terminal word
   assert(dict_spell(d, "cart'd")==NULL);
   // Put it in
   assert(dict_addword(d, "cart'd"));
   // It's now there
   assert(dict_spell(d, "Cart'd"));
   // New nodes were created
   assert(dict_nodecount(d)==9);
   assert(dict_wordcount(d)==4);

   // Only one of each word at the moment
   assert(dict_mostcommon(d)==1);
   // Increments the freq variable
   // Should return false (repeat)
   assert(!dict_addword(d, "cart"));
   // Now 'cart' has been added twice 
   assert(dict_mostcommon(d)==2);
   // But no new nodes were created
   assert(dict_nodecount(d)==9);
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
   // 7 new nodes: p+a+r+t+e+d+r
   assert(dict_nodecount(d)==16);
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
   int nodec[DICTFILES] = {5640, 161558, 18792};
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
      // No word is added twice
      assert(dict_mostcommon(d)==mostc[i]);
      // Hard to test for ...
      assert(dict_nodecount(d)==nodec[i]);
      assert(dict_wordcount(d)==wc);
   }

/* Leave this commented out to begin with
// !!!!!!!!!!!!!!!!!!!!!!!
// 10% : DICT_AUTOCOMPLETE
   d = dict_init();
   assert(d);
   dict_addword(d, "carting");
   dict_addword(d, "carter");
   dict_addword(d, "carting");
   dict_addword(d, "carted");
   dict_addword(d, "carting");
   dict_addword(d, "cart");
   dict_addword(d, "carting");
   dict_addword(d, "car");
   dict_addword(d, "carting");

   // We've made sure carting is
   // a frequently-occuring word ...
   dict_autocomplete(d, "c", str);
   assert(strcmp(str, "arting")==0);
   dict_autocomplete(d, "carte", str);
   // Alphabetically carted not carter
   assert(strcmp(str, "d")==0);

   // Use the Pride & Prejudice
   // dictionary built above
   p = dcts[2];
   dict_autocomplete(p, "t", str);
   // 'the' is most common word that 
   // can be found from 't'
   assert(strcmp(str, "he")==0);
   // But given 'the' what comes after it?
   dict_autocomplete(p, "thei", str);
   // their ...
   assert(strcmp(str, "r")==0);
   // This story is about the bennet family:
   dict_autocomplete(p, "ben", str);
   assert(strcmp(str, "net")==0);

// !!!!!!!!!!!!!!
// 10% : DICT_CMP
   dict* p1 = dict_spell(d, "cart");
   dict* p2 = dict_spell(d, "carter");
   // 2 steps up from 'carter' is 'cart'
   assert(dict_cmp(p1, p2)==2);
   p1 = dict_spell(d, "carted");
   // 1 step up to 'carte' and 1 back down again
   assert(dict_cmp(p1, p2)==2);

   p1 = dict_spell(dcts[0], "aback");
   p2 = dict_spell(dcts[0], "zonal");
   // 5 moves to top, 5 moves back down again
   assert(dict_cmp(p1, p2)==10);
   dict_free(&d);
*/

   // Free up all those dictionaries
   for(int i=0; i<DICTFILES; i++){
      dict_free(&dcts[i]);
   }

   return 0;
}
