CFLAGS = -Wall -Wextra -Werror -Wfloat-equal -pedantic -std=c99 -Wvla -O3
ARRPATH = ../IndexedArray/Realloc
GENPATH = ../../../../Git/ADTs/General
TARGET = testset
INCS = -I$(ARRPATH)/.. -I$(GENPATH)/


all: $(TARGET)

testset: testset.c Realloc/realloc.c set.h $(ARRPATH)/realloc.c $(ARRPATH)/../arr.h $(GENPATH)/general.h $(GENPATH)/general.c
	$(CC) -g testset.c Realloc/realloc.c $(GENPATH)/general.c $(ARRPATH)/realloc.c $(INCS) -o $@ $(CFLAGS)

clean:
	rm -fr $(TARGET)

memleak: $(TARGET)
	valgrind --error-exitcode=1 --quiet --leak-check=full ./$(TARGET)


run: all
	./testset

.PHONY: clean run all
