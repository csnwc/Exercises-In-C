.PHONY: all clean run rund

all: t27 t27_d

t27: t27.c t27.h driver.c
	gcc driver.c t27.c -Wall -Wextra -Wpedantic -Wvla -Wfloat-equal -std=c99 -O3 -o t27

t27_d: t27.c t27.h driver.c
	gcc driver.c t27.c -Wall -Wextra -Wpedantic -Wvla -Wfloat-equal -std=c99 -fsanitize=undefined -fsanitize=address -g3 -o t27_d

run: t27
	./t27

rund: t27_d
	./t27_d

clean:
	rm -f t27 t27_d
