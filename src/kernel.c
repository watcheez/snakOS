#include "system.h"
#include "icons.h"

extern void main() {
    idt_install();
    isrs_install();
    irq_install();
    init_palette();

    __asm__ __volatile__ ("sti");


    for (size_t i  = 0; i < 40; i++) {
        writeChar(i % 40, i / 40, (i%10) + '0');
    }

    drawIcon(98, 50, logo);

}