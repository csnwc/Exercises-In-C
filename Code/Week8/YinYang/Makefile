CFLAGS := -Wall -Wextra -pedantic -std=c99 -Wfloat-equal -Wvla -Werror
DEBUG := -g3 -fsanitize=address -fsanitize=undefined
OPTIM := -O3
CC := gcc # Try clang too

all: yy yy_d

yy: driver.c yy.c yy.h
	$(CC) driver.c yy.c $(CFLAGS) $(OPTIM) -o yy -lm

yy_d: driver.c yy.c yy.h
	$(CC) driver.c yy.c $(CFLAGS) $(DEBUG) -o yy_d -lm

clean:
	rm -f ./yy_d ./yy
