CFLAGS := -Wall -Wextra -Wpedantic -Wvla -Wfloat-equal -std=c99 -Werror
SANITIZE := -fsanitize=undefined -fsanitize=address -g3
OPTIMIZE := -O3
CC := gcc # Also check clang

all: run rund

nm: nm.c nm.h driver.c mydefs.h
	$(CC) driver.c nm.c $(CFLAGS) $(OPTIMIZE) -o nm

nm_d: nm.c nm.h driver.c mydefs.h
	$(CC) driver.c nm.c $(CFLAGS) $(SANITIZE) -o nm_d

run: nm
	./nm

rund: nm_d
	./nm_d

clean:
	rm -f nm nm_d extension

extension: ext.c ext_nm.h driver.c ext_mydefs.h
	$(CC) driver.c ext.c $(CFLAGS) $(OPTIMIZE) -o extension

