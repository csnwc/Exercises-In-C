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

// Prototype necessary for lisp_reduce() tests only */
void times(lisp* l, atomtype* n);
void  atms(lisp* l, atomtype* n);

void test(void);

int main(void)
{
   test();
   char str[LISTSTRLEN];
   printf("Test Lisp (%s) Start ... ", LISPIMPL);

   lisp_tostring(NIL, str);
   assert(lisp_length(NIL)==0);
   assert(strcmp(str, "()")==0);

   assert(lisp_isatomic(NULL)==false);
   lisp* a1 = atom(2);
   assert(lisp_length(a1)==0);
   assert(lisp_isatomic(a1)==true);
   lisp_free(&a1);
   assert(a1==NULL);

   lisp* l1 = cons(atom(2), NIL);
   assert(l1);
   assert(lisp_length(l1)==1);
   lisp_tostring(l1, str);
   assert(strcmp(str, "(2)")==0);
   assert(lisp_getval(car(l1))==2);
   assert(lisp_isatomic(l1)==false);
   assert(lisp_isatomic(l1->car)==true);

   lisp* l2 = cons(atom(1), l1);
   assert(l2);
   assert(lisp_length(l2)==2);
   lisp_tostring(l1, str);
   lisp_tostring(l2, str);
   assert(strcmp(str, "(1 2)")==0);

   lisp* l3 = cons(atom(3), cons(atom(4), cons(atom(5), NIL)));
   assert(l3);
   assert(lisp_length(l3)==3);
   lisp_tostring(l3, str);
   assert(strcmp(str, "(3 4 5)")==0);

   lisp* l4 = cons(l2, l3);
   assert(l4);
   assert(lisp_length(l4)==4);
   lisp_tostring(l4, str);
   assert(strcmp(str, "((1 2) 3 4 5)")==0);

   lisp* l5 = cons(atom(0), l4);
   assert(l5);
   assert(lisp_length(l5)==5);
   lisp_tostring(l5, str);
   assert(strcmp(str, "(0 (1 2) 3 4 5)")==0);


   /* ------------------------- */
   /* lisp_car & lisp_cdr tests */
   /* ------------------------- */
   /*
    (defvar l6 (car l1)) output=2
    (defvar l7 (cdr l3)) output=(4 5)
    (defvar l8 (car(cdr(cdr(l5))))) output=3
   */
   lisp* l6 = car(l1);
   lisp_tostring(l6, str);
   // This is not a list, therefore not bracketed.
   assert(strcmp(str, "2")==0);
   lisp* l7 = cdr(l3);
   lisp_tostring(l7, str);
   assert(strcmp(str, "(4 5)")==0);
   lisp* l8 = car(cdr(cdr(l5)));
   lisp_tostring(l8, str);
   // This is not a list, therefore not bracketed.
   assert(strcmp(str, "3")==0);

   /*-----------------*/
   /* lisp_copy tests */
   /*-----------------*/
   /*
    (defvar l9 (copy-list l5)) output=(0 (1 2) 3 4 5)
   */
   lisp* l9 = copy(l5);
   lisp_tostring(l9, str);
   assert(strcmp(str, "(0 (1 2) 3 4 5)")==0);
   // OK, it's the same as l5, but is it deep?
   lisp_free(&l9);
   assert(!l9);

   /* All other lists have been re-used to build l5
      so no need to free l4, l3 etc.*/
   lisp_free(&l5);
   assert(!l5);

   lisp* l10 = cons(atom(7), cons(atom(3), cons(atom(8), NIL)));
   // Adds a ill-defined cons struct to the front of the list 
   // lisp_getval(l10) is undefined - but shouldn't crash your program.
   lisp* l12 = lisp_cons(NULL, l10); 
   assert(lisp_length(l12)==lisp_length(l10)+1);
   lisp_free(&l12);
   

   /*-------------------------*/
   /* lisp_fromstring() tests */ 
   /*-------------------------*/
   char inp[4][LISTSTRLEN] = {"()", "(1)", "(0 (1 -2) 3 4 50)", "((-1 2) (3 4) (5 (6 7)))"};
   for(int i=0; i<4; i++){
      lisp* f1 = fromstring(inp[i]);
      lisp_tostring(f1, str);
      assert(strcmp(str, inp[i])==0);
      lisp_free(&f1);
      assert(!f1);
   }

   /*--------------------*/
   /* lisp_list() tests  */
   /*--------------------*/
   lisp* g1 = lisp_list(3, atom(6), atom(7), atom(8));
   lisp_tostring(g1, str);
   assert(strcmp(str, "(6 7 8)")==0);
   lisp* g2 = lisp_list(5, g1, atom(-123456), copy(g1), atom(25),
                        fromstring("(1(2(3(4 5))))"));
   lisp_tostring(g2, str);
   assert(strcmp(str, "((6 7 8) -123456 (6 7 8) 25 (1 (2 (3 (4 5)))))")==0);
   // g2 reuses g1, so no need to lisp_free(g1)
   lisp_free(&g2);
   assert(!g2);

   /*--------------------------------------------------*/
   /* lisp_reduce() tests - calls func for every atom  */
   /*--------------------------------------------------*/
   lisp* h1 = lisp_fromstring("(1 2 3 4)");
   lisp* h2 = lisp_fromstring("(1 2 (7) 3)");
   atomtype acc = 1;
   lisp_reduce(times, h1, &acc);
   assert(acc==24);
   acc = 1;
   lisp_reduce(times, h2, &acc);
   assert(acc==42);
   acc = 0;
   lisp_reduce(atms, h1, &acc);
   assert(acc=4);
   acc = 0;
   lisp_reduce(atms, h2, &acc);
   assert(acc=4);
   lisp_free(&h1);
   assert(!h1);
   lisp_free(&h2);
   assert(!h2);
   printf("End\n");
   return 0;
}

// Multiplies getval() of all atoms
void times(lisp* l, atomtype* accum)
{
   *accum = *accum * lisp_getval(l);
}

// To count number of atoms in list, including sub-lists
void atms(lisp* l, atomtype* accum)
{
   // Could just add one (since each node must be atomic),
   // but prevents unused warning for variable 'l'...
   *accum = *accum + lisp_isatomic(l);
}
