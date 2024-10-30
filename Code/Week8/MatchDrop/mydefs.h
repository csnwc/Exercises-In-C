#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <stdbool.h>

#define BRDSZ 6
#define MAXBRDS 200000

/*
Here define struct state -
mine included an array of
struct board{
   2D array of tiles
   hawk
}

struct state{
    array of board[];
    etc.
}
*/

#include "md.h"
