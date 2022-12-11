# First 20 Fibonacci Numbers 
(
   (SET L '(1 0)')
   (SET C '2')
   (WHILE (LESS C '20') (
      (SET N (PLUS (CAR L)  (CAR (CDR L))))
      (SET M (CONS N L))
      (SET L M)
      (SET B (PLUS '1' C))
      (SET C B)
   ))
   (PRINT M)
)
