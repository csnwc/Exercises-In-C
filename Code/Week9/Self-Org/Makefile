CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
GENERAL= ../../ADTs/General
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: testlinked_s testlinked_v testlinked build_s build uniq uniq_s

testlinked_s: soll.h Linked/specific.h Linked/linked.c testsoll.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) testsoll.c Linked/linked.c $(GENERAL)/general.c -o testlinked_s -I./Linked -I./$(GENERAL) $(SANITIZE) $(LDLIBS)

testlinked_v: soll.h Linked/specific.h Linked/linked.c testsoll.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) testsoll.c Linked/linked.c $(GENERAL)/general.c -o testlinked_v -I./Linked -I./$(GENERAL) $(VALGRIND) $(LDLIBS)

testlinked: soll.h Linked/specific.h Linked/linked.c testsoll.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) testsoll.c Linked/linked.c $(GENERAL)/general.c -o testlinked -I./Linked -I./$(GENERAL) $(PRODUCTION) $(LDLIBS)

build: soll.h Linked/specific.h Linked/linked.c build.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) build.c Linked/linked.c $(GENERAL)/general.c -o build -I./Linked -I./$(GENERAL) $(PRODUCTION) $(LDLIBS)

build_s: soll.h Linked/specific.h Linked/linked.c build.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) build.c Linked/linked.c $(GENERAL)/general.c -o build_s -I./Linked -I./$(GENERAL) $(SANITIZE) $(LDLIBS)

uniq: soll.h Linked/specific.h Linked/linked.c uniq.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) uniq.c Linked/linked.c $(GENERAL)/general.c -o uniq -I./Linked -I./$(GENERAL) $(PRODUCTION) $(LDLIBS)

uniq_s: soll.h Linked/specific.h Linked/linked.c uniq.c $(GENERAL)/general.h $(GENERAL)/general.c
	$(CC) uniq.c Linked/linked.c $(GENERAL)/general.c -o uniq_s -I./Linked -I./$(GENERAL) $(SANITIZE) $(LDLIBS)

testlinked_v: soll.h Linked/specific.h Linked/linked.c testsoll.c $(GENERAL)/general.h $(GENERAL)/general.c

clean:
	rm -f testlinked_s testlinked_v testlinked build_s build uniq uniq_s

run: all
	./testlinked_s
	valgrind ./testlinked_v
	./build_s ../../Data/Words/s-and-s-words.txt
	./uniq_s ../../Data/Words/s-and-s-words.txt ../../Data/Words/p-and-p-words.txt

