#ifndef MEMFUNC_H
#define MEMFUNC_H

#include "types.h"

extern uint8_t *memcpy(uint8_t * dest, const uint8_t * src, int count);
extern uint8_t *memset(uint8_t * dest, uint8_t val, int count);
extern uint16_t *memsetw(uint16_t * dest, uint16_t val, int count);
extern int strlen(const char *str);
extern uint8_t inportb(uint16_t _port);
extern void outportb(uint16_t _port, uint8_t _data);

#endif