CFLAGS := -Wall -Wextra -pedantic -std=c99 -Wfloat-equal -Wvla -Werror
AVX    := -mavx2 -march=native
DEBUG  :=  -g3 -fsanitize=address -fsanitize=undefined
OPTIM  := -O3
CC     := gcc # Try clang too

all: ahash ahash_d exthash exthash_d

run: all
	./ahash
	./ahash_d
	./exthash
	./exthash_d

ahash_d: ahash.c ahash.h driver.c
	$(CC) driver.c ahash.c $(CFLAGS) $(DEBUG) -o ahash_d -lm

ahash: ahash.c ahash.h driver.c
	$(CC) driver.c ahash.c $(CFLAGS) $(OPTIM) -o ahash -lm

exthash:   exthash.c ahash.h driver.c
	$(CC) driver.c exthash.c $(CFLAGS) $(AVX) $(OPTIM) -o exthash -lm

exthash_d:   exthash.c ahash.h driver.c
	$(CC) driver.c exthash.c $(CFLAGS) $(AVX) $(DEBUG) -o exthash_d -lm


clean:
	rm -f ahash ahash_d exthash exthash_d
