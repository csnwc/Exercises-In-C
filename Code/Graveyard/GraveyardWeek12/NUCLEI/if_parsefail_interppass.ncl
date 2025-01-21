# The parser examines all of the language, therefore fails when it gets to 'GARBAGE'
(
   (IF (EQUAL '1' '1') ((PRINT "YES"))((GARBAGE)))
)
