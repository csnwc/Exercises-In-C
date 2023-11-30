CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3

all: driverbsa_s driverbsa # extfibmemo_s

driverbsa_s: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) driver.c Alloc/alloc.c -o driverbsa_s -I./Alloc $(SANITIZE)

driverbsa: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) driver.c Alloc/alloc.c -o driverbsa -I./Alloc $(PRODUCTION)

fibmemo_s: bsa.h Alloc/specific.h Alloc/alloc.c fibmemo.c
	$(CC) fibmemo.c Alloc/alloc.c -o fibmemo_s -I./Alloc $(SANITIZE)

## Only if you do an extension. Uncomment in all, extfibmemo_s and run.
extfibmemo_s: bsa.h Extension/specific.h Extension/extension.c fibmemo.c
	$(CC) fibmemo.c Extension/extension.c -o extfibmemo_s -I./Extension $(SANITIZE)

run: driverbsa driverbsa_s fibmemo_s # extfibmemo_s
	./driverbsa
	./driverbsa_s
	./fibmemo_s
	#./extfibmemo_s

clean:
	rm -f driverbsa_s driverbsa fibmemo_s extfibmemo_s
