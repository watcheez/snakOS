#ifndef TYPES_H
#define TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef long unsigned int uint64_t;

typedef uint32_t size_t;

struct regs 
{
    uint32_t gs, fs, es, ds;                            /* Pushed the segs last */
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;    /* pushed by 'pusha' */
    uint32_t int_no, err_code;                          /* our 'push byte #' and error codes */
    uint32_t eip, cs, eflags, useresp, ss;              /* Pushed by the processor automatically */
};

struct icon {
    uint32_t width;
    uint32_t height;
    const uint8_t *data;
};

#endif