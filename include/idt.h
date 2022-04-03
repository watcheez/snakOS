#ifndef IDT_H
#define IDT_H

#include "types.h"

/*
  7  | 6 5  | 4 3 2 1 0
  P  | DPL  | 0 1 1 1 0 (14)

  P: Segment is present ? (1 = YES) should be 1
  DPL: Which ring (0 to 3) should be 00

*/

struct idt_entry
{
    uint16_t base_lo;
    uint16_t sel;           /* Our kernel segment goes here! */
    uint8_t always0;        /* This wille ALWAYS be set to 0! */
    uint8_t flags;          /* Set using the above table! */
    uint16_t base_hi;
}__attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

/* ASM function */
extern void idt_load();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_install();

#endif