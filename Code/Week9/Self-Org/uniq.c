/*
Find which words appear in argv[2] but not argv[1] :
Usage : ./uniqs ../../Data/Words/p-and-p.txt ../../Data/Words/s-and-s.txt
Or, for a very simple spelling-checker (that could take 5mins or more to run ...) :
Usage : ./uniqs ../../Data/Words/eng_370k_shuffle.txt ../../Data/Words/s-and-s.txt
leads to ~60 words being "misspelled".
*/

#include "soll.h"

#define MAXSTR 1000

int main(int argc, char* argv[])
{
   if(argc != 3){
      fprintf(stderr, "Usage : %s <words1.txt> <words2.txt>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   char str[MAXSTR];
   long cnt = 0;
   soll* allwds = soll_init(mtf);
   soll* uniqs = soll_init(mtf);

   FILE* fp = nfopen(argv[1], "rt");
   bool done = false;
   do{
      if(fscanf(fp, "%s", str) != 1){
         done = true;
      }
      else{
         if(!soll_isin(allwds, str, &cnt)){
            soll_add(allwds, str);
         }
      }
   }while(!done);
   fclose(fp);

   fp = nfopen(argv[2], "rt");
   done = false;
   do{
      if(fscanf(fp, "%s", str) != 1){
         done = true;
      }
      else{
         if(!soll_isin(allwds, str, &cnt)){
            soll_add(allwds, str);
            soll_add(uniqs, str);
            printf("%s\n", str);
         }
      }
   }while(!done);
   fclose(fp);

   printf("All Words = %d (Pointer-chases:%ld)\n", soll_size(allwds), cnt);
   printf("Words in 2nd file, but not in first = %d\n", soll_size(uniqs));
   soll_free(allwds);
   soll_free(uniqs);

   return EXIT_SUCCESS;

}
