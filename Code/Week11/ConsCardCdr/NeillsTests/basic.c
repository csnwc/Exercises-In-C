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

#define nassert(X) if(X){ printf("STANDARD TEST (line %d) OK\n[1 MARK-BASIC BASIC%d]\n", __LINE__, __LINE__); fflush(stdout); }else{ printf("STANDARD TEST (line %d) FAIL\n[0 MARK-BASIC BASIC%d]\n", __LINE__, __LINE__); fflush(stdout); }

// Prototype necessary for lisp_reduce() tests only */
void times(lisp* l, atomtype* n);
void  atms(lisp* l, atomtype* n);

void test(void);

int main(void)
{
   //test();
   char str[LISTSTRLEN];

   lisp_tostring(NIL, str);
   nassert(lisp_length(NIL)==0);
   nassert(strcmp(str, "()")==0);

   nassert(lisp_isatomic(NULL)==false);
   lisp* a1 = atom(2);
   nassert(lisp_length(a1)==0);
   nassert(lisp_isatomic(a1)==true);
   lisp_free(&a1);
   nassert(a1==NULL);

   lisp* l1 = cons(atom(2), NIL);
   nassert(l1);
   nassert(lisp_length(l1)==1);
   lisp_tostring(l1, str);
   nassert(strcmp(str, "(2)")==0);
   nassert(lisp_getval(car(l1))==2);
   nassert(lisp_isatomic(l1)==false);
   nassert(lisp_isatomic(lisp_car(l1))==true);

   lisp* l2 = cons(atom(1), l1);
   nassert(l2);
   nassert(lisp_length(l2)==2);
   lisp_tostring(l1, str);
   lisp_tostring(l2, str);
   nassert(strcmp(str, "(1 2)")==0);

   lisp* l3 = cons(atom(3), cons(atom(4), cons(atom(5), NIL)));
   nassert(l3);
   nassert(lisp_length(l3)==3);
   lisp_tostring(l3, str);
   nassert(strcmp(str, "(3 4 5)")==0);

   lisp* l4 = cons(l2, l3);
   nassert(l4);
   nassert(lisp_length(l4)==4);
   lisp_tostring(l4, str);
   nassert(strcmp(str, "((1 2) 3 4 5)")==0);

   lisp* l5 = cons(atom(0), l4);
   nassert(l5);
   nassert(lisp_length(l5)==5);
   lisp_tostring(l5, str);
   nassert(strcmp(str, "(0 (1 2) 3 4 5)")==0);


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
   nassert(strcmp(str, "2")==0);
   lisp* l7 = cdr(l3);
   lisp_tostring(l7, str);
   nassert(strcmp(str, "(4 5)")==0);
   lisp* l8 = car(cdr(cdr(l5)));
   lisp_tostring(l8, str);
   // This is not a list, therefore not bracketed.
   nassert(strcmp(str, "3")==0);

   /*-----------------*/
   /* lisp_copy tests */
   /*-----------------*/
   /*
    (defvar l9 (copy-list l5)) output=(0 (1 2) 3 4 5)
   */
   lisp* l9 = copy(l5);
   lisp_tostring(l9, str);
   nassert(strcmp(str, "(0 (1 2) 3 4 5)")==0);
   // OK, it's the same as l5, but is it deep?
   lisp_free(&l9);
   nassert(!l9);

   /* All other lists have been re-used to build l5
      so no need to free l4, l3 etc.*/
   lisp_free(&l5);
   nassert(!l5);

   lisp* l10 = cons(atom(7), cons(atom(3), cons(atom(8), NIL)));
   // Adds a ill-defined cons struct to the front of the list 
   // lisp_getval(l10) is undefined - but shouldn't crash your program.
   lisp* l12 = lisp_cons(NULL, l10); 
   nassert(lisp_length(l12)==lisp_length(l10)+1);
   lisp_free(&l12);
   
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
