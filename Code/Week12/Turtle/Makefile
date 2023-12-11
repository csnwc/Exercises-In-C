CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3

all: parse_s interp_s

parse_s: Parse/parse.h Parse/parse.c
	$(CC) Parse/parse.c -o parse_s -I./Parse $(SANITIZE) -lm

interp_s: Interp/interp.h Interp/interp.c neillsimplescreen.c neillsimplescreen.h
	$(CC) neillsimplescreen.c Interp/interp.c -o interp_s -I./Interp $(SANITIZE) -lm

### An example : you may wish to adapt this slightly
extension_s: Extension/extension.h Extension/extension.c neillsimplescreen.c neillsimplescreen.h
	$(CC) neillsimplescreen.c Extension/extension.c -o extension_s -I./Extension $(SANITIZE) -lm

run: all
	./parse_s TTLs/empty.ttl
	./parse_s TTLs/forward.ttl
	./parse_s TTLs/ok_parse_fail_interp.ttl
	./parse_s TTLs/set1.ttl
	./parse_s TTLs/donothing.ttl
	./parse_s TTLs/set2.ttl
	./parse_s TTLs/turn.ttl
	./parse_s TTLs/spiral.ttl
	./parse_s TTLs/octagon1.ttl
	./parse_s TTLs/octagon2.ttl
	./parse_s TTLs/tunnel.ttl
	./parse_s TTLs/labyrinth.ttl
	./parse_s TTLs/hypno.ttl
	./parse_s TTLs/5x5.ttl
	./parse_s TTLs/downarrow.ttl
	./interp_s TTLs/empty.ttl out_empty.txt
	./interp_s TTLs/forward.ttl out_forward.txt
	./interp_s TTLs/set1.ttl out_set1.txt
	./interp_s TTLs/donothing.ttl out_donothing.txt
	./interp_s TTLs/fail_parse_ok_interp.ttl out_fail_parse_ok_interp.txt
	./interp_s TTLs/set2.ttl out_set2.txt
	./interp_s TTLs/turn.ttl out_turn.txt
	./interp_s TTLs/spiral.ttl out_spiral.txt
	./interp_s TTLs/octagon1.ttl out_octagon1.txt
	./interp_s TTLs/octagon2.ttl out_octagon2.txt
	./interp_s TTLs/tunnel.ttl out_tunnel.txt
	./interp_s TTLs/labyrinth.ttl out_labyrinth.txt
	./interp_s TTLs/hypno.ttl out_hypno.txt
	./interp_s TTLs/5x5.ttl out_5x5.txt
	./interp_s TTLs/downarrow.ttl out_downarrow.txt
	./interp_s TTLs/empty.ttl out_empty.ps
	./interp_s TTLs/forward.ttl out_forward.ps
	./interp_s TTLs/set1.ttl out_set1.ps
	./interp_s TTLs/donothing.ttl out_donothing.ps
	./interp_s TTLs/fail_parse_ok_interp.ttl out_fail_parse_ok_interp.ps
	./interp_s TTLs/set2.ttl out_set2.ps
	./interp_s TTLs/turn.ttl out_turn.ps
	./interp_s TTLs/spiral.ttl out_spiral.ps
	./interp_s TTLs/octagon1.ttl out_octagon1.ps
	./interp_s TTLs/octagon2.ttl out_octagon2.ps
	./interp_s TTLs/tunnel.ttl out_tunnel.ps
	./interp_s TTLs/labyrinth.ttl out_labyrinth.ps
	./interp_s TTLs/hypno.ttl out_hypno.ps
	./interp_s TTLs/5x5.ttl out_5x5.ps
	./interp_s TTLs/downarrow.ttl out_downarrow.ps

clean:
	rm -f parse_s interp_s out_*.txt out_*.ps out_*.pdf
