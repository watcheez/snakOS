#include "memfunc.h"

extern uint8_t *memcpy(uint8_t * dest, const uint8_t * src, int count)
{
    size_t i;

    for (i = 0; i<count; ++i) {
        *(dest + i) = *(src + i);
    }

    return dest;
}

extern uint8_t *memset(uint8_t * dest, uint8_t val, int count)
{
    size_t i;

    for (i = 0; i<count; ++i) {
        *(dest + i) = val;
    }

    return dest;
}

extern uint16_t *memsetw(uint16_t * dest, uint16_t val, int count)
{
    size_t i;

    for (i = 0; i<count; ++i) {
        *(dest + i) = val;
    }

    return dest;
}

extern int strlen(const char *str)
{
    int count = 0;

    while (*(str + count) != '\0') {
        ++count;
    }
    return count;
}

extern uint8_t inportb(uint16_t _port)
{
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

extern void outportb(uint16_t _port, uint8_t _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}