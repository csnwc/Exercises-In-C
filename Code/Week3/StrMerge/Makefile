CC := gcc # also try clang
CFLAGS := -Wall -Wextra -pedantic -std=c99 -Wvla -Wfloat-equal
OPT := -O3
DBG := -g3 -fsanitize=address -fsanitize=undefined

run: strmerge_dbg strmerge
	./strmerge
	./strmerge_dbg

strmerge: strmerge.c
	$(CC) strmerge.c $(CFLAGS) $(OPT) -o strmerge

strmerge_dbg: strmerge.c
	$(CC) strmerge.c $(CFLAGS) $(DBG) -o strmerge_dbg

clean: 
	rm -f strmerge strmerge_dbg
