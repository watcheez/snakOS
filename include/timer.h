#ifndef TIMER_H
#define TIMER_H

#include "types.h"

void timer_handler(struct regs *r);
void timer_install();
void timer_wait(uint32_t ticks);
void timer_phase(uint32_t hz);
void addTimerListener(void (*listener)());
void removeTimerListener(void (*listener)());
uint16_t get_random_uint16(uint16_t max);

#endif