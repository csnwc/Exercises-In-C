# The grammar only defines a LITERAL as being single-quoted - this is fine for the parser.
# However, when you interpret, lisp_tostring() (or similar) fails.
(
   (SET A '((1 2')
)
