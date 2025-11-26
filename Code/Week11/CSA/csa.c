#include "csa.h"
#include "mydefs.h"

csa* csa_init()
{
}

bool csa_get(csa* c, int idx, int* val)
{
}

bool csa_set(csa* c, int idx, int val)
{
}

void csa_tostring(csa* c, char* s)
{
}

void csa_free(csa** l)
{
}

void test(void)
{
}

#ifdef EXT
void csa_foreach(void (*func)(int* p, int* ac), csa* c, int* ac)
{
}

bool csa_delete(csa* c, int indx)
{
}
#endif
