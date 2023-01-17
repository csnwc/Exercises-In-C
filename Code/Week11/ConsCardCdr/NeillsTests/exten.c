#include "lisp.h"
#include "specific.h"

// It's more Lisp-like to call it cons() etc., not lisp_cons()
#define atom(X)       lisp_atom(X)
#define cons(X, Y)    lisp_cons(X, Y)
#define car(L)        lisp_car(L)
#define cdr(L)        lisp_cdr(L)
#define copy(L)       lisp_copy(L)
#define fromstring(L) lisp_fromstring(L)
// It's more Lisp-like to call it NIL, not NULL
#define NIL NULL

#define LISTSTRLEN 1000

/* I checked some of these tests via a common lisp implementation:
   # sudo apt install sbcl
   # sbcl --script test.lsp
*/

#define nassert(X) if(X){ printf("STANDARD EXTENSION TEST (line %d) OK\n[1 MARK-EXTEN EXTENSION%d]\n", __LINE__, __LINE__); fflush(stdout); }else{ printf("STANDARD EXTENSION TEST (line %d) FAIL\n[0 MARK-EXTEN EXTENSION%d]\n", __LINE__, __LINE__); fflush(stdout); }

// Prototype necessary for lisp_reduce() tests only */
void sms(lisp* l, atomtype* n);
void  atms(lisp* l, atomtype* n);

void test(void);

int main(void)
{
   char str[LISTSTRLEN];
   
   /*-------------------------*/
   /* lisp_fromstring() tests */ 
   /*-------------------------*/
   char inp[4][LISTSTRLEN] = {"()", "(1 2 5)", "((1 -2) 3 (4 50))", "((-1 2) (3 4) (5 (6 7)))"};
   for(int i=0; i<4; i++){
      lisp* f1 = fromstring(inp[i]);
      lisp_tostring(f1, str);
      printf("\n");
      nassert(strcmp(str, inp[i])==0);
      lisp_free(&f1);
      nassert(!f1);
   }

   /*--------------------*/
   /* lisp_list() tests  */
   /*--------------------*/
   lisp* g1 = lisp_list(3, atom(6), atom(7), atom(8));
   lisp_tostring(g1, str);
   nassert(strcmp(str, "(6 7 8)")==0);
   lisp* g2 = lisp_list(5, g1, atom(-123456), copy(g1), atom(25),
                        fromstring("(1(2(3(4 5))))"));
   lisp_tostring(g2, str);
   nassert(strcmp(str, "((6 7 8) -123456 (6 7 8) 25 (1 (2 (3 (4 5)))))")==0);
   // g2 reuses g1, so no need to lisp_free(g1)
   lisp_free(&g2);
   nassert(!g2);

   /*--------------------------------------------------*/
   /* lisp_reduce() tests - calls func for every atom  */
   /*--------------------------------------------------*/
   lisp* h1 = lisp_fromstring("(-1 -2 -3 -4)");
   lisp* h2 = lisp_fromstring("(1 2 (7) 3)");
   atomtype acc = 1;
   lisp_reduce(sms, h1, &acc);
   nassert(acc==-10);
   acc = 1;
   lisp_reduce(sms, h2, &acc);
   nassert(acc==13);
   acc = 0;
   lisp_reduce(atms, h1, &acc);
   nassert(acc==4);
   acc = 0;
   lisp_reduce(atms, h2, &acc);
   nassert(acc==4);
   lisp_free(&h1);
   nassert(!h1);
   lisp_free(&h2);
   nassert(!h2);
   return 0;
}

// To count number of atoms in list, including sub-lists
void atms(lisp* l, atomtype* accum)
{
   // Could just add one (since each node must be atomic),
   // but prevents unused warning for variable 'l'...
   *accum = *accum + lisp_isatomic(l);
}

// To count number of atoms in list, including sub-lists
void sms(lisp* l, atomtype* accum)
{
   // Could just add one (since each node must be atomic),
   // but prevents unused warning for variable 'l'...
   *accum = *accum + lisp_getval(l);
}
