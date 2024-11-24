/* A 'tree 27' implementation
   of the Dictionary ADT */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// 26 letters, plus the '
#define ALPHA 27

// You'd normally not expose this structure
// to the user, and it's members should *never*
// be used in e.g. driver.c
struct dict {
   // 'Down' pointers next letter of word a-z or '
   struct dict* dwn[ALPHA];
   /* The parent pointer, useful for
      traversing back up the tree */
   struct dict* up; 
   // Is this node the end of a word?
   bool terminal;
   // Store occurences of the *same* word
   // Only used in terminal nodes
   int freq;
};
typedef struct dict dict;

// Creates new dictionary
dict* dict_init(void);

/* Top of Dictionary = p,
   add word str. Return false
   if p or str is NULL, or if word
   is already in the dictionary.
   True otherwise.
*/
bool dict_addword(dict* p, const char* wd);

/* The total number of nodes
   in the tree. */
int dict_nodecount(const dict* p);

/* Total number of times that any words
   have been added into the tree =
   sum of freq count of all terminals.*/
int dict_wordcount(const dict* p);

/* Returns the dict* where str is
   marked as 'terminal', or else NULL.
*/
dict* dict_spell(const dict* p, const char* str);

/* Frees all memory used by dictionary p.
   Sets the original pointer back to NULL */
void dict_free(dict** p);

/* Returns number of times most common
   word in dictionary has been added
   (when you insert a word and it already
   exists, increment the count)
*/
int dict_mostcommon(const dict* p);

/* CHALLENGE1
   For two nodes, count the nodes that separate them */
unsigned dict_cmp(dict* p1, dict* p2);

/* CHALLENGE2
   For dictionary 'p', and word 'wd', find the
   path down to the most frequently used word
   below this node, adding these letters to 'ret'.
   In the event of ties, use the word that comes
   first alphabetically. Treat the apostrophe as
   alphabetically greater than all letters */
void dict_autocomplete(const dict* p, const char* wd, char* ret);

void test(void);
