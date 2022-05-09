#ifndef VGA_H
#define VGA_H

#include "types.h"

extern void init_palette();
extern void drawPixel(uint32_t x, uint32_t y, uint8_t color);
extern void drawIcon(uint32_t x, uint32_t y, struct icon icon);
extern void writeChar(uint32_t x, uint32_t y, unsigned char c);
extern void writeString(uint32_t x, uint32_t y, const unsigned char * str);
extern void clearScreen();

#endif