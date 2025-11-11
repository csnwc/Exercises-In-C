// Do not change this file.
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct pair {
   int x1, y1, x2, y2;
};
typedef struct pair pair;

// mydefs.h : You create this
#include "ext_mydefs.h"

/* n is used to seed srand(). Then numbers are
generated to fill the board row-wise,
left to right, top down. Each number = rand()%9+1.
rand() is compiler dependent, but I've tested this
with gcc and clang on WSL2 and the lab machines.
*/
board randfill(int n);

/* Returns true if the pair of numbers
in the board p are a valid match or not i.e.
they are the same or sum to ten, and are either
touching, or are on a straight line with no other
numbers between.
*/
bool take(board* p, pair z);

/* Returns true if the board can be solved using
the exact (breadth-first) method outlined in the
exercise, false if not.
*/
bool solve(int seed);

/* Test all your functions - my driver.c is not
rigorous.
*/
void test(void);
