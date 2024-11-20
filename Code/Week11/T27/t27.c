#include "t27.h"

// 'Internal' function prototypes 
// ...

dict* dict_init(void)
{
}

bool dict_addword(dict* p, const char* wd)
{
}

void dict_free(dict** d)
{
}

int dict_wordcount(const dict* p)
{
}

int dict_nodecount(const dict* p)
{
}

dict* dict_spell(const dict* p, const char* str)
{
}

int dict_mostcommon(const dict* p)
{
}

// CHALLENGE1
unsigned dict_cmp(dict* p1, dict* p2)
{
}

// CHALLENGE2
void dict_autocomplete(const dict* p, const char* wd, char* ret)
{
}
