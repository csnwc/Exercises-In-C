#include "ahash.h"

#define NAMES2IPS "hostname_ip_mappings_25k.txt"
#define WORDS "eng_370k_shuffle.txt"

uint32_t fnv32_hash(const char *str);
uint32_t djb2_hash(const char *str);
uint32_t terrible_hash(const char *str);
uint32_t worst_hash(const char *str);

void _printdetail(ahash* a);

int main(void)
{

   test();

   char  key[MAXKV];
   char val1[MAXKV];
   char val2[MAXKV];

   // Some of the AVX checks assume this
   assert(PERBUCKET==16);

   #ifdef __AVX__
      printf("AVX ON : ");
      // Some of the AVX checks assume this
      assert(PERBUCKET==16);
   #else
      printf("AVX OFF : ");
   #endif

   // Make sure we have __SANITIZE_ADDRESS__ with both clang & gcc
   #if defined(__has_feature)
      #if __has_feature(address_sanitizer) && !defined(__SANITIZE_ADDRESS__) // for clang
         #define __SANITIZE_ADDRESS__ // gcc already sets this
      #endif
   #endif
   #ifdef __SANITIZE_ADDRESS__
      printf("Sanitizer ON\n");
   #else
      printf("Sanitizer OFF\n");
   #endif

   ahash* a = ahash_init(fnv32_hash);
   FILE* fp = fopen(NAMES2IPS, "rt");
   if(!fp){
      fprintf(stderr, "Cannot open %s?\n", NAMES2IPS);
      exit(EXIT_FAILURE);
   }
   while(fscanf(fp, "%s %s", key, val1) == 2){
      // Do an insert
      assert(ahash_insert(&a, key, val1));
   }
   fclose(fp);

   fp = fopen(NAMES2IPS, "rt");
   if(!fp){
      fprintf(stderr, "Cannot open %s?\n", NAMES2IPS);
      exit(EXIT_FAILURE);
   }
   while(fscanf(fp, "%s %s", key, val1)==2){
      // Get the value back again
      bool b = ahash_isin(a, key, val2);
      assert(b);
      // Check they're the same
      assert(strcmp(val1, val2)==0);
   };
   fclose(fp);

   ahash_free(&a);
   assert(a==NULL);

   // To create a spellchecker, stores each word as the key - no need for a value here though ...
   a = ahash_init(fnv32_hash);
   fp = fopen(WORDS, "rt");
   if(!fp){
      fprintf(stderr, "Cannot open %s?\n", WORDS);
      exit(EXIT_FAILURE);
   }
   while(fscanf(fp, "%s", key) == 1){
      // Do an insert
      assert(ahash_insert(&a, key, ""));
      // Get the value back again
      assert(ahash_isin(a, key, val1));
      assert(val1[0]=='\0');
   }
   fclose(fp);

   fp = fopen(WORDS, "rt");
   if(!fp){
      fprintf(stderr, "Cannot open %s?\n", WORDS);
      exit(EXIT_FAILURE);
   }
   while(fscanf(fp, "%s", key) == 1){
      assert(ahash_delete(&a, key));
   }
   fclose(fp);
   ahash_free(&a);
   assert(a==NULL);


//-----------------------------------------------------
// ahash_ctrl stuff

   #define BIGSTR 1000
   char ctl[BIGSTR];
   // Everything goes into bucket 0 
   a = ahash_init(worst_hash);
   // After 12th insertion, load > 70%, resize
   for(int i=0; i<16; i++){
      sprintf(key, "%02d", i);
      assert(ahash_insert(&a, key, ""));
   }
   sprintf(key, "%02d", 16);
   assert(ahash_insert(&a, key, ""));
   ahash_ctrl(a, ctl);
   assert(!strcmp(ctl, "FFFF|8000|0000|0000"));
   ahash_free(&a);
   assert(a==NULL);

   a = ahash_init(fnv32_hash);
   for(int i=0; i<11; i++){
      sprintf(key, "%02d", i);
      assert(ahash_insert(&a, key, ""));
   }
   // After 12th insertion, load > 70%, resize
   sprintf(key, "%02d", 11);
   assert(ahash_insert(&a, key, ""));
   ahash_ctrl(a, ctl);
   assert(!strcmp(ctl, "F800|C000|C000|E000"));
   assert(ahash_delete(&a, "00"));
   // A deleted key is still marked as "In Use"
   assert(strcmp(ahash_ctrl(a, ctl), "F800|C000|C000|E000"));

   // Delete most keys, table will be shrunk
   for(int i=1; i<11; i++){
      sprintf(key, "%02d", i);
      assert(ahash_delete(&a, key));
   }
   ahash_ctrl(a, ctl);
   assert(strcmp(ctl, "4000")==0);
   ahash_free(&a);
   assert(a==NULL);

   return EXIT_SUCCESS;
}

/*
 * I've seen this in a commercial piece of S/W :-(
 */
uint32_t terrible_hash(const char *str)
{
   int len = strlen(str);
   return (str[0]+str[len-1])*len;
}

uint32_t worst_hash(const char *str)
{
   // To stop unused variable warnings :-(
   assert(str[0]);
   // Always return 0 !
   return 0;
}

uint32_t djb2_hash(const char* s)
{
    uint32_t hash = 5381;
    int c;
    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

uint32_t fnv32_hash(const char *s)
{
    /* See the FNV parameters at www.isthe.com/chongo/tech/comp/fnv/#FNV-param */
    const uint32_t FNV_32_PRIME = 0x01000193; /* 16777619 */
    uint32_t h = 0x811c9dc5; /* 2166136261 */
    while (*s){
        /* xor the bottom with the current octet */
        h ^= *s++;
        /* multiply by the 32 bit FNV magic prime mod 2^32 */
        h *= FNV_32_PRIME;
    }
    return h;
}
