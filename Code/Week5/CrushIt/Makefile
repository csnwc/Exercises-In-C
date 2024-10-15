WARNS := -Wall -Wextra -Wfloat-equal -Wvla -std=c99 -Wpedantic
DEBUG := -fsanitize=undefined -fsanitize=address -g3
OPTIM := -O3

crushit: crushit.c driver.c crushit.h mydefs.h
	gcc driver.c crushit.c $(WARNS) $(OPTIM) -o crushit

crushit_d: crushit.c driver.c crushit.h mydefs.h
	gcc driver.c crushit.c $(WARNS) $(DEBUG) -o crushit_d

run: crushit_d
	./crushit_d

# Your submission must contain exactly two files
zip:
	zip crushit.zip crushit.c mydefs.h

clean:
	rm -f crushit_d crushit
