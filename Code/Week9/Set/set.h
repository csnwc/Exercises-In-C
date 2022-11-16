#pragma once

/*
A Set ADT - based on an underlying arr ADT. Here:
1. No element can appear twice
2. No particular ordering of elements is implied
*/

typedef struct set set;

/* Create empty set */
set* set_init(void);
/* Create new set, copied from another */
set* set_copy(set* s);
/* Create new set, copied from an array of length n*/
set* set_fromarray(int* a, int n);

/* Basic Operations */
/* Add one element into the set */
void set_insert(set* s, int l);
/* Return size of the set */
int set_size(set* s);
/* Returns true if l is in the array, false elsewise */
int set_contains(set* s, int l);
/* Remove l from the set (if it's in) */
void set_remove(set* s, int l);
/* Remove one element from the set - there's no
   particular order for the elements, so any will do */
int set_removeone(set* s);

/* Operations on 2 sets */
/* Create a new set, containing all elements from s1 & s2 */
set* set_union(set* s1, set* s2);
/* Create a new set, containing all elements in both s1 & s2 */
set* set_intersection(set* s1, set* s2);

/* Finish up */
/* Clears all space used, and sets pointer to NULL */
void set_free(set** s);
