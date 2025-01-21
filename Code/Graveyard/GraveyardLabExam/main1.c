#include <assert.h>
#include <string.h>

#define STR 50

/* Takes the input string and copies it into the output string,
   concealing all digits apart from the last four.
   Only digits are altered - anything else is left unaltered.
   The string 'input' is Read-Only */
void conceal(const char input[], char output[]);

int main(void)
{

   char out[STR];

   conceal("1234-567-8900", out);
   assert(strcmp(out, "****-***-8900")==0);

   conceal("123456789", out);
   assert(strcmp(out, "*****6789")==0);

   conceal("Lloyds Bank 0345-1278-9", out);
   assert(strcmp(out, "Lloyds Bank ****-*278-9")==0);

   conceal("471", out);
   assert(strcmp(out, "471")==0);

   conceal("", out);
   assert(strcmp(out, "")==0);
   
   return 0;
}
