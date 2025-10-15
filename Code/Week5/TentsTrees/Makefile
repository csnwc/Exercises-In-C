CFLAGS := -Wall -Wextra -pedantic -std=c99 -Wfloat-equal -Wvla -g3 -fsanitize=address -fsanitize=undefined
#CFLAGS := -Wall -Wextra -pedantic -std=c99 -Wfloat-equal -Wvla -Werror -g3 -fsanitize=address -fsanitize=undefined
CC := gcc
#CC := clang

run: tt6_d tt4_d
	./tt6_d
	./tt4_d

tt6_d: driver.c tt.c tentstrees.h
	$(CC) driver.c tt.c $(CFLAGS) -DBSIZE=6 -o tt6_d

tt4_d: driver.c tt.c tentstrees.h
	$(CC) driver.c tt.c $(CFLAGS) -DBSIZE=4 -o tt4_d

clean:
	rm -f tt6_d tt4_d
