#ifndef PRINT_H
#define PRINT_H

#include "types.h"


#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define YELLOW 14
#define WHITE 15

extern void print_char(const uint8_t c, uint8_t forecolour, uint8_t backcolour, int x, int y);
extern void print_string(const uint8_t * msg, uint8_t forecolour, uint8_t backcolour, int x, int y);
void clear();

#endif