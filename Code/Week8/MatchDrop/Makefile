# General flags we'll always use
GENFLAGS := -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal 

# -O3 means optimise compiled code for execution speed
OPTIM := $(GENFLAGS) -O3

# Creates a much slower executable but filled with run-time error/bounds checking etc.
# -g flag gives extra debugging information
SANITIZE := $(GENFLAGS) -g3 -fsanitize=address -fsanitize=undefined

# In the labs you might use clang, but make sure to try gcc too
# (sometimes bugs show up 'better' using one compiler than another
# CC := gcc
CC := clang

md: driver.c md.c md.h mydefs.h
	$(CC) driver.c md.c $(OPTIM) -o md

md_d: driver.c md.c md.h mydefs.h
	$(CC) driver.c md.c $(SANITIZE) -o md_d

all: md md_d

run:
	./md

clean:
	rm -f md md_d md.zip

# Create a .zip file of required files
zip: 
	zip -r md.zip md.c mydefs.h
