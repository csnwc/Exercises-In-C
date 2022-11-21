CC=clang
GENPATH=../../../../Git/ADTs/General
COMMON= -Wall -Wextra -Wfloat-equal -Wvla -Wpedantic -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: testrealloc_s testrealloc_v testrealloc

testrealloc : boolarr.h Realloc/specific.h Realloc/realloc.c testboolarr.c $(GENPATH)/general.h $(GENPATH)/general.c
	$(CC) testboolarr.c Realloc/realloc.c $(GENPATH)/general.c -o testrealloc -I./Realloc -I$(GENPATH) $(PRODUCTION) $(LDLIBS)

testrealloc_s : boolarr.h Realloc/specific.h Realloc/realloc.c testboolarr.c $(GENPATH)/general.h $(GENPATH)/general.c
	$(CC) testboolarr.c Realloc/realloc.c $(GENPATH)/general.c -o testrealloc_s -I./Realloc -I$(GENPATH) $(SANITIZE) $(LDLIBS)

testrealloc_v : boolarr.h Realloc/specific.h Realloc/realloc.c testboolarr.c $(GENPATH)/general.h $(GENPATH)/general.c
	$(CC) testboolarr.c Realloc/realloc.c $(GENPATH)/general.c -o testrealloc_v -I./Realloc -I$(GENPATH) $(VALGRIND) $(LDLIBS)


clean:
	rm -f testrealloc_s testrealloc_v testrealloc

run: all
	./testrealloc_s
	valgrind ./testrealloc_v
