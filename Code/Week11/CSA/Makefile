CFLAGS := -Wall -Wextra -pedantic -std=c99 -Wfloat-equal -Wvla -Werror
SANI   := -g3 -fsanitize=address -fsanitize=undefined
OPTIM  := -O3
CC := gcc # Try clang too

run: csa csa_s fibmemo
	./csa
	./csa_s
	./fibmemo

csa: driver.c csa.c mydefs.h
	$(CC) driver.c csa.c $(CFLAGS) $(OPTIM) -o csa

csa_s: driver.c csa.c mydefs.h
	$(CC) driver.c csa.c $(CFLAGS) $(SANI) -o csa_s

fibmemo: fibmemo.c csa.c mydefs.h
	$(CC) fibmemo.c csa.c $(CFLAGS) $(OPTIM) -o fibmemo

## Extension 1 : foreach()
factorials: isfactorial.c csa.c mydefs.h
	$(CC) -DEXT isfactorial.c csa.c $(CFLAGS) $(OPTIM) -o factorials

## Extension 2
csa_ext: driver.c csa.c mydefs.h
	$(CC) -DEXT driver.c csa.c $(CFLAGS) $(OPTIM) -o csa_ext

primes: sieve.c csa.c mydefs.h
	$(CC) -DEXT sieve.c csa.c $(CFLAGS) $(OPTIM) -o primes

runall: run factorials primes csa_ext
	./factorials
	./primes
	./csa_ext

clean:
	rm -f csa csa_s factorials primes csa_ext fibmemo
