CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
# You'll probably need to change this path to somewhere we've you've stored general.c/.h
GENERAL= ../../../../ADTs/General
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: testlinked_s testlinked_v testlinked

testlinked_s: lisp.h Linked/specific.h Linked/linked.c testlisp.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) testlisp.c Linked/linked.c $(GENERAL)/general.c -o testlinked_s -I./Linked -I./$(GENERAL) $(SANITIZE) $(LDLIBS)

testlinked_v: lisp.h Linked/specific.h Linked/linked.c testlisp.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) testlisp.c Linked/linked.c $(GENERAL)/general.c -o testlinked_v -I./Linked -I./$(GENERAL) $(VALGRIND) $(LDLIBS)

testlinked: lisp.h Linked/specific.h Linked/linked.c testlisp.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) testlisp.c Linked/linked.c $(GENERAL)/general.c -o testlinked -I./Linked -I./$(GENERAL) $(PRODUCTION) $(LDLIBS)

clean:
	rm -f testlinked_s testlinked_v testlinked

run: all
	./testlinked_s
	valgrind --quiet ./testlinked_v
