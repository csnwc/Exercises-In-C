FLGS := -Wall -Wextra -pedantic -std=c99 -Wvla -Wfloat-equal -g3 -fsanitize=address -fsanitize=undefined

wordle: main.c wordle.c
	gcc main.c wordle.c $(FLGS) -o wordle

clean: 
	rm -fr wordle