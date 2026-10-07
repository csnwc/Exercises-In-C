CMPLR := gcc # also try clang
FLGS := -Wall -Wextra -pedantic -std=c99 -Wvla -Wfloat-equal
OPT := -O3
DBG := -g3 -fsanitize=address -fsanitize=undefined

run: clean strmerge_dbg strmerge
	./strmerge_dbg
	./strmerge

strmerge: strmerge.c
	$(CMPLR) strmerge.c $(FLGS) $(OPT) -o strmerge

strmerge_dbg: strmerge.c
	$(CMPLR) strmerge.c $(FLGS) $(DBG) -o strmerge_dbg

clean: 
	rm -fr strmerge strmerge_dbg
