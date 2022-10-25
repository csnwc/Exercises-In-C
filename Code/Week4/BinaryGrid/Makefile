# Use clang, but could be gcc
CC=clang

# Our 'core' set of flags used for everything
BASEFLAGS=-Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal

# Optimise code, but allow no warnings during compilation
PRODFLAGS=$(BASEFLAGS) -O1
# Be super tough - fail to compile if *any* errors
# PRODFLAGS=$(BASEFLAGS) -O1 -Werror

# Not optimisation, add in Sanitizer code -> huge executable file but will tell you if an array goes out-of-bounds etc.
DBGFLAGS=$(BASEFLAGS) -fsanitize=address -fsanitize=undefined -g3 
LDLIBS= -lm

all : bingrid bingrid_dbg

# Production Code - no warnings allowed, no sanitizer
bingrid : bingrid.c bingrid_driver.c bingrid.h
	$(CC) bingrid.c bingrid_driver.c -o bingrid $(PRODFLAGS) $(LDLIBS)

# Development Code - sanitizer enabled
bingrid_dbg : bingrid.c bingrid_driver.c bingrid.h
	$(CC) bingrid.c bingrid_driver.c -o bingrid_dbg $(DBGFLAGS) $(LDLIBS)

all: bingrid bingrid_dbg

clean:
	rm -f bingrid bingrid_dbg
