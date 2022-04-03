#include "system.h"

extern void main() {
    idt_install();
    isrs_install();
    irq_install();

    __asm__ __volatile__ ("sti");

    for (size_t i = 0; i < 80; ++i) {
        for (size_t j = 0; j < 25; ++j) {
            print_char(254, YELLOW, BLACK, i, j);
        }
    }
    print_string("Hello world! My name is SnakOs :) ", WHITE, BLACK, 0, 1);
}