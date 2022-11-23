#include "general.h"

typedef struct soll soll;

typedef enum{none, mtf, transpose} orgtype;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
Create an empty soll. Can be of type:
'none'      : Unsorted linked list.
'mtf'       : When element is accessed it is moved to the front.
'transpose' : When element is accessed it is moved one place closer to the front.
*/
soll* soll_init(orgtype type);

/*
Add element onto end having freq=1 regardless of whether it exists
elsewhere in the list. str is deeply *copied* into the list,
so the user of the ADT is free to delete 'str' afterwards.
*/
void soll_add(soll* s, char* str);

// Take element out
bool soll_remove(soll* s, char* str);

/*
Does the word str exist in list ? Returns Boolean after searching via pointer
chasing through the list from start -> end.
When the word is found, frequency is incremented & list might be reorganised,
depending on s->type.
Parameter 'cnt' keeps a total count of the total number of times we
pointer-chase elements in the list.
*/
bool soll_isin(soll* s, char* str, long* cnt);

/*
Returns frequency of a particular element.
Does not alter the state of the list in any way.
*/
int soll_freq(soll* s, char* str);

// Returns number of words in list
int soll_size(soll* s);

// Returns stringified version of list
void soll_tostring(soll* s, char* str);

// Clears up all space used
bool soll_free(soll* s);
