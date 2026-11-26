#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>

// Maximum string len of key/value
#define MAXKV 50

// Slots per bucket
// When implementing AVX, assume this is always 16
#define PERBUCKET 16 

// Number of buckets initially
#define INITBUCKETS 1
// Once table is too full => increase buckets
#define EXPANDFACT 4
// Once more Tombstones than keys => decrease buckets
#define SHRINKFACT 2

// Expand if load% is greater than this
#define MAXLOAD 70

// leftmost bit set to 1
#define EMPTY     0x80 // 10000000
#define TOMBSTONE 0xff // 11111111

typedef struct data {
   // Key
   char k[MAXKV]; 
   // Value
   char v[MAXKV];
} data;

typedef uint8_t ctrl;

typedef struct alpinehash {
   // Control byte cells
   ctrl* c;
   // Data (key/value) cells
   data* d;
   // Table is numbuckets*PERBUCKET elements
   int numbuckets;
   // Number of elements currently active
   int nkeys;
   // Number of tombstones (due to deletion)
   int ntombs;
   // Function to be used for hashing
   uint32_t (*hashfunc)(const char *str);
} ahash;

// Returns a pointer to the initial empty/small table.
// Pass the name of the function used to perform hashing.
ahash* ahash_init(uint32_t (*f)(const char *str));

// If the table has become too small to hold the data, it is
// resized (EXPANDFACT). Therefore, the pointer might change
// so we need to pass a pointer-to-the-pointer.
// Insert key/val pair if key is new, or else update val if
// key already exists.
// Resize if load% > MAXLOAD
bool ahash_insert(ahash** a, const char* key, const char* val);

// Clear all memory & set the pointer to NULL once successful
void ahash_free(ahash** a);

// If key exists in table, copy val & return true. Else false.
bool ahash_isin(const ahash* a, const char* key, char* val);

// Delete an element from the table - this is done by tombstoning
// the control byte (you can't truly set it to empty because this
// key might have formed part of a probe chain).
// If the hashtable has more tombstones than elements, then
// shrink (SHRINKFACT) and rehash.
// After delete (nkeys+ntombs) is the same, assuming no rehash.
bool ahash_delete(ahash** a, const char* key);

/// Optional
// Return a string corresponding to which slots in a control string
// are in use (not EMPTY OR TOMBSTONE).
// When only one slot is in use (and one bucket) the output in ret
// is "0xF0" i.e. left-most bit is set.
// Function returns pointer to ret, to enable easier use of strcmp().
char* ahash_ctrl(const ahash* a, char* ret);

void test(void);
