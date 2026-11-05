CFLAGS := -Wall -Wextra -pedantic -std=c99 -Wfloat-equal -Wvla -Werror
DEBUG := -g3 -fsanitize=address -fsanitize=undefined
OPTIM := -O3
CC := gcc # Try clang too

all: yy yy_d # ext
	./yy
	./yy_d
	# ./ext

yy: driver.c yy.c mydefs.h yy.h
	$(CC) driver.c yy.c $(CFLAGS) $(OPTIM) -o yy -lm

yy_d: driver.c yy.c mydefs.h yy.h
	$(CC) driver.c yy.c $(CFLAGS) $(DEBUG) -o yy_d -lm

ext: driver.c yy.h ext_mydefs.h ext.c
	$(CC) driver.c ext.c $(CFLAGS) $(OPTIM) -o ext -lm

clean:
	rm -f ./yy_d ./yy ./ext
