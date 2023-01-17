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

#define nassert(X) if(X){ printf("STANDARD_ALTTEST (line %d) OK\n[1 MARK-BASIC BASICALT%03d]\n", __LINE__, __LINE__); fflush(stdout); }else{ printf("STANDARD_ALT TEST (line %d) FAIL\n[0 MARK-BASIC BASICALT%d]\n", __LINE__, __LINE__); fflush(stdout); }

void test(void);

int main(void)
{
   //test();
   char str[LISTSTRLEN];

   lisp* l1 = cons(atom(2), cons(atom(5), NIL));
   nassert(l1);
   nassert(lisp_length(l1)==2);
   lisp_tostring(l1, str);
   nassert(strcmp(str, "(2 5)")==0);
   nassert(lisp_getval(car(l1))==2);
   nassert(lisp_isatomic(l1)==false);
   nassert(lisp_isatomic(lisp_car(lisp_cdr(l1)))==true);

   lisp* l2 = cons(l1, NIL);
   nassert(l2);
   nassert(lisp_length(l2)==1);
   lisp_tostring(l2, str);
   nassert(strcmp(str, "((2 5))")==0);

   lisp* l1c = copy(l1);
   lisp* l3 = cons(l1c, cons(atom(3), cons(atom(4), cons(atom(5), NIL))));
   lisp_tostring(l3, str);
   nassert(strcmp(str, "((2 5) 3 4 5)")==0);

   lisp* l4 = cons(l3, NIL);
   nassert(lisp_length(l4)==1);
   lisp_tostring(l4, str);
   nassert(strcmp(str, "(((2 5) 3 4 5))")==0);
  
   lisp* l5 = cons(atom(100), NIL);
   nassert(lisp_length(l5)==1);
   lisp_tostring(l5, str);
   nassert(strcmp(str, "(100)")==0);
   lisp_free(&l5);

   lisp* l6 = copy(l4);
   lisp_free(&l4);
   nassert(lisp_length(l6)==1);
   lisp_free(&l6);
   lisp_free(&l2);
   nassert(!l6);

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
