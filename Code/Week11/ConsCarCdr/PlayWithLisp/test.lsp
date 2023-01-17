;;; This is a Lisp Program
;;; For interest only / highly optional
;;; To install a version of Lisp :
;;; sudo apt install sbcl
;;; then to run this lisp program :
;;; sbcl --script test.lsp


;;; A Lisp function to 'draw' the car/cdr structures
(load "sdraw.generic")

;;; The following broadly follows testlisp.c 
(print (eq (length NIL) 0))

(defvar l1 (cons 2 NIL))
(print l1)
(print (eq (length l1) 1))
(sdraw l1)

(defvar l2 (cons 1 l1))
(print l2)
(print (eq (length l2) 2))
(sdraw l2)

(defvar l3 (cons 3 (cons 4 (cons 5 NIL))))
(print l3)
(print (eq (length l3) 3))
(sdraw l3)

(defvar l4 (cons l2 l3))
(print l4)
(print (eq (length l4) 4))
(sdraw l4)

(defvar l5 (cons 0 l4))
(print l5)
(print (eq (length l5) 5))
(sdraw l4)
(sdraw l5)

(defvar l6 (car l1))
(print l6)
(defvar l7 (cdr l3))
(print l7)
(defvar l8 (car (cdr (cdr l5))))
(print l8)

(defvar l9 (copy-list l5))
(print l9)
(fresh-line)

;;; No real equivalent for lisp_fromstring(), so skip

(defvar g1 (list 6 7 8))
(print g1)
(defvar g2 (list g1 -123456 (copy-list g1) 25 '(1(2(3(4 5))))))
(print g2)
(sdraw g2)
(fresh-line)
