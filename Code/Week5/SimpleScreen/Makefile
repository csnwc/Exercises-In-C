# Use clang, but could be gcc
CC=clang

# Our 'core' set of flags used for everything
BASEFLAGS=-Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal

# Optimise code, but allow no warnings during compilation
PRODFLAGS=$(BASEFLAGS) -O1 -Werror

# Not optimisation, add in Sanitizer code -> huge executable file but will tell you if an array goes out-of-bounds etc.
DBGFLAGS=$(BASEFLAGS) -fsanitize=address -fsanitize=undefined -g3 
LDLIBS= -lm

# Library linking : maths
LIBS =  -lm 

all: demo_neillsimplescreen

demo_neillsimplescreen: demo_neillsimplescreen.c neillsimplescreen.c neillsimplescreen.h
	$(CC) demo_neillsimplescreen.c neillsimplescreen.c -o demo_neillsimplescreen $(PRODFLAGS) $(LIBS)

clean:
	rm -f demo_neillsimplescreen

run: demo_neillsimplescreen
	./demo_neillsimplescreen
