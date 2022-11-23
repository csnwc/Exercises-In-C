/*
Compare the 3 methods of self-organisation when building a list of all
words appearing in a text file.
Usage : ./build ../../Git/Data/Words/p-and-p.txt
(Some the later assertions assume the file contains the word "and"!)
*/

#include "soll.h"

#define MAXSTR 1000

soll* builddict(char* name, char* fname, orgtype type);

int main(int argc, char* argv[])
{
   if(argc != 2){
      fprintf(stderr, "Usage : %s <book.txt>\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   soll* sn, *st, *sm;

   sn = builddict("None", argv[1], none);
   st = builddict("Transpose", argv[1], transpose);
   sm = builddict("MTF", argv[1], mtf);

   assert(soll_freq(sn, "and")==soll_freq(sm, "and"));
   assert(soll_freq(sn, "and")==soll_freq(st, "and"));
   printf("\nThe word \"and\" appears %d times\n", soll_freq(st, "and"));

   assert(soll_free(sn));
   assert(soll_free(st));
   assert(soll_free(sm));
   return EXIT_SUCCESS;
}

soll* builddict(char* name, char* fname, orgtype type)
{
   char str[MAXSTR];
   long cnt = 0;
   soll* s = soll_init(type);
   printf("%9s : ", name);
   FILE* fp = nfopen(fname, "rt");
   bool done = false;
   do{
      if(fscanf(fp, "%s", str) != 1){
         done = true;
      }
      else{
         //printf("Word = %s\n", str);
         if(!soll_isin(s, str, &cnt)){
            soll_add(s, str);
         }
      }
   }while(!done);
   fclose(fp);
   printf("Unique Words=%d (Pointer-chases:%ld)\n", soll_size(s), cnt);
   return s;
}
