CFLAGS := -Wall -Wextra -pedantic -std=c99 -Wfloat-equal -Wvla -g3 -fsanitize=address -fsanitize=undefined -Werror
CC := gcc # Try clang too

run: crowns_d
	./crowns_d

crowns_d: driver.c crowns.c crowns.h lut.o
	$(CC) driver.c crowns.c lut.o $(CFLAGS) -o crowns_d -lm

clean:
	rm -f crowns_d
