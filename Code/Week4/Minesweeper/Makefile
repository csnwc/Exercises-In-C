# Gneral flags we'll always use (-Werror will prevent code generation if *any* errors)
GENFLAGS := -Wall -Wextra -pedantic -std=c99 -Wvla -Wfloat-equal -Werror

# -O2 means optimise comiled code for execution speed
OPTIM := $(GENFLAGS) -O2

# Use the sanitizer - do real-time bounds checking etc. etc.
DEBUG := $(GENFLAGS) -g3 -fsanitize=undefined -fsanitize=address

# In the labs you'll proably use clang, but make sure to try gcc too
CC := clang

all: ms ms_sani

ms: ms.c tst.c ms.h
	$(CC) ms.c tst.c $(OPTIM) -o ms

ms_sani: ms.c tst.c ms.h
	$(CC) ms.c tst.c $(DEBUG) -o ms_sani

clean:
	rm -f ms ms_sani

run: all
	./ms
	./ms_sani
