#ifndef VGA_H
#define VGA_H

#include "types.h"

extern void init_palette();
extern void drawPixel(uint32_t x, uint32_t y, uint8_t color);
extern void drawIcon(uint32_t x, uint32_t y, struct icon icon);
extern void writeChar(uint32_t x, uint32_t y, unsigned char c);
extern void writeCharBackground(uint32_t x, uint32_t y, unsigned char c, uint8_t background);
extern void writeString(uint32_t x, uint32_t y, const unsigned char * str);
extern void writeStringBackground(uint32_t x, uint32_t y, const unsigned char * str, uint8_t background);
extern void writeInt(uint32_t x, uint32_t y, uint32_t integer);
extern void writeIntBackground(uint32_t x, uint32_t y, uint32_t integer, uint8_t background);
extern void clearScreen();
extern void drawTexture8x8(uint8_t id, uint8_t x, uint8_t y, uint8_t color);
extern void setScreenColor(uint8_t color);

#endif