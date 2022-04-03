#include "print.h"
#include "memfunc.h"

extern void print_char(const uint8_t c, uint8_t forecolour, uint8_t backcolour, int x, int y)
{
    uint16_t color = (backcolour << 4) | (forecolour & 0x0f);
    volatile uint16_t * location;
    location = (volatile uint16_t *)0xB8000 + (y * 80 + x);
    *location = c | (color << 8);
}

extern void print_string(const uint8_t * msg, uint8_t forecolour, uint8_t backcolour, int x, int y)
{
    size_t i;
    uint16_t color;
    volatile uint16_t * location;
    uint8_t counter = 0;

    i = 0;
    color = (backcolour << 4) | (forecolour & 0x0f);
    location = (volatile uint16_t *)0xB8000 + (y * 80 + x);
    
    while (*(msg+i) != 0 && location < (volatile uint16_t *)(0xB8000 + 4000)) {
        *location = *(msg+i) | (color << 8);
        ++i;
        ++location;
        ++counter;
    }
}

extern void clear()
{
    uint32_t blank;
    size_t i;
    uint16_t * location;

    blank = 0x20 | (0x0f << 8);
    

    for (i = 0; i < 25; ++i) {
        location = (uint16_t *)0xB8000 + (i * 80);
        memsetw(location, blank, 80);
    }
}