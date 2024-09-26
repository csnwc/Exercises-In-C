FLGS := -Wall -Wextra -pedantic -std=c99 -Wvla -Wfloat-equal -g3 -fsanitize=address -fsanitize=undefined

rot18: main.c rot18.c rot18.h
	gcc main.c rot18.c $(FLGS) -o rot18

clean: 
	rm -fr rot18