#include "../include/mem.h"


void *memset(void *s, int c, size_t n)
{
    unsigned char *p = (uint8_t *)s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

void *memcpy(void *dest, const void *src, size_t n)
{
	void *tmp = dest;
	uint8_t *d = (uint8_t *)dest;
	uint8_t *s = (uint8_t *)src;


	for( ; n; n--, d++, s++)
		*(uint8_t *)d = *(uint8_t *)s;

	return tmp;
}