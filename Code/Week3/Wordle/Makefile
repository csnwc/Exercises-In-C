CMPLR := gcc # also try clang
FLGS := -Wall -Wextra -pedantic -std=c99 -Wvla -Wfloat-equal
OPT := -O3
DBG := -g3 -fsanitize=address -fsanitize=undefined

run: wordle wordle_dbg
	./wordle_dbg
	./wordle

wordle: main.c wordle.c
	$(CMPLR) main.c wordle.c $(FLGS) $(OPT) -o wordle

wordle_dbg: main.c wordle.c
	$(CMPLR) main.c wordle.c $(FLGS) $(DBG) -o wordle_dbg

clean: 
	rm -fr wordle wordle_dbg