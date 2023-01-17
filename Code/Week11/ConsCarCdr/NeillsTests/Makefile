CC=clang
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 #-Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
# You'll probably need to change this path to somewhere we've you've stored general.c/.h
GENERAL=/home/csnwc/Lecturing/ComsM1201/Git/ADTs/General
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: basic basicalt_s exten

basic: ../../lisp.h Linked/specific.h Linked/linked.c ../../basic.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) ../../basic.c Linked/linked.c $(GENERAL)/general.c -o basic -I.. -I../.. -I./Linked -I$(GENERAL) $(PRODUCTION) $(LDLIBS)

basicalt_s: ../../lisp.h Linked/specific.h Linked/linked.c ../../basicalt.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) ../../basicalt.c Linked/linked.c $(GENERAL)/general.c -o basicalt_s -I.. -I../.. -I./Linked -I$(GENERAL) $(SANITIZE) $(LDLIBS)

exten: ../../lisp.h Linked/specific.h Linked/linked.c ../../exten.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) ../../exten.c Linked/linked.c $(GENERAL)/general.c -o exten -I.. -I../.. -I./Linked -I$(GENERAL) $(PRODUCTION) $(LDLIBS)

clean:
	@rm -f testlinked_s testlinked_v testlinked basic basicalt_s exten


testlinked_s: ../../lisp.h Linked/specific.h Linked/linked.c ../../testlisp.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) ../../testlisp.c Linked/linked.c $(GENERAL)/general.c -o testlinked_s -I.. -I/.../.. -I./Linked -I$(GENERAL) $(SANITIZE) $(LDLIBS)

testlinked_v: ../../lisp.h Linked/specific.h Linked/linked.c ../../testlisp.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) ../../testlisp.c Linked/linked.c $(GENERAL)/general.c -o testlinked_v -I.. -I../.. -I./Linked -I$(GENERAL) $(VALGRIND) $(LDLIBS)

testlinked: ../../lisp.h Linked/specific.h Linked/linked.c ../../testlisp.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) ../../testlisp.c Linked/linked.c $(GENERAL)/general.c -o testlinked -I.. -I../.. -I./Linked -I$(GENERAL) $(PRODUCTION) $(LDLIBS)

