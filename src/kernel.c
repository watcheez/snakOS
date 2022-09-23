#include "system.h"

extern void main() {
    idt_install();
    isrs_install();
    irq_install();
    init_palette();
    timer_install();
    keyboard_install();

    __asm__ __volatile__ ("sti");

    load_menu();
}