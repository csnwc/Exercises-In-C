# Use clang in the labs & not gcc, especially for sanitizer...
CC= clang

# Our 'core' set of flags used for everything
COREFLAGS= -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal

# 'Standard' compilation
STANFLAGS= $(COREFLAGS) -O1

# Sanitizer Flags
SANIFLAGS= $(COREFLAGS) -fsanitize=address -fsanitize=undefined -g3 

# Don't think anyone will actually need the maths lib...
LDLIBS= -lm

all : conceal conceal_s inkblot inkblot_s

# Standard Build: type "make conceal" or "make inkblot"
conceal : main1.c conceal.c
	$(CC) main1.c conceal.c -o conceal $(STANFLAGS) $(LDLIBS)
inkblot : main2.c inkblot.c
	$(CC) main2.c inkblot.c -o inkblot $(STANFLAGS) $(LDLIBS)

# Sanitizer Code: type "make conceal_s" or "make inkblot_s"
conceal_s : main1.c conceal.c
	$(CC) main1.c conceal.c -o conceal_s $(SANIFLAGS) $(LDLIBS)
inkblot_s : main2.c inkblot.c
	$(CC) main2.c inkblot.c -o inkblot_s $(SANIFLAGS) $(LDLIBS)

clean:
	rm -f conceal conceal_s inkblot inkblot_s
