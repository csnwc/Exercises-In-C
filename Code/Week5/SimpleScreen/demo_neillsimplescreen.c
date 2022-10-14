/* Print a simple count-down to demonstrate
   the use of neillsimplescreen - a couple of
   very simple functions to move the cursor top-left
   and change the foreground text colour - only
   works on ANSI compliant terminals - see source
   for more details */

#include "neillsimplescreen.h"

int main(void)
{

   neillcol c;
   /* Don't keep clearing the screen,
      you'll get flickering */
   neillclrscrn();
   for(c=red; c<=white; c++){
      neillfgcol(c);
      neillbgcol(white);
      neillcursorhome();
      printf("\n\n\n\n\n\t%02d\n", (white-c)+1);
      neillbusywait(1.0);
   }
   /* Return colours to normal */
   neillreset();
   return 0;
}
