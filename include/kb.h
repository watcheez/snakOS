#ifndef KB_H
#define KB_H

#include "types.h"

void keyboard_handler(struct regs *r);
void keyboard_install();
void addKbListener(void (*listener)(char c));
void removeKbListener(void (*listener)(char c));

#endif