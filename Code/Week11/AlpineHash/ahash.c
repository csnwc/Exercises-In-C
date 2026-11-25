#include "ahash.h"

ahash* ahash_init(uint32_t (*h)(const char *str))
{
}

bool ahash_insert(ahash** p, const char* k, const char* v)
{
}

bool ahash_isin(const ahash* a, const char* k, char* v)
{
}

bool ahash_delete(ahash** a, const char* k)
{
}

void ahash_free(ahash** p)
{
}

char* ahash_ctrl(const ahash* a, char* ret)
{
}
