#include "idt.h"
#include "memfunc.h"


/*
 * Declare an IDT of 256 entries. Although we will only use the first 32 entries here.
 * The rest exists as a bit of a trap. If any undefined IDT entry is hit, it normally will
 * Cause an "Unhandlded Interrupt" exception. Any descriptor for which the 'presence' bit
 * is cleared (0) will generate an "Unhandled Interrupt" exception.
 */
struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt[num].base_lo = (uint16_t)(base & 0x0000ffff);
    idt[num].base_hi = (uint16_t)(base >> 16);
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_install()
{
    /* Sets the special IDT pointer up*/
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t) &idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset((uint8_t *) &idt, 0, sizeof(struct idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();

}