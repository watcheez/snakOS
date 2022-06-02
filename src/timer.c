#include <timer.h>
#include <irq.h>
#include <vga.h>
#include <memfunc.h>


uint32_t timer_ticks = 0;
uint32_t i = 0;


void timer_handler(struct regs *r)
{
    timer_ticks++;
    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (timer_ticks % 100 == 0)
    {
        writeChar(i % 40, i / 40, (i%10) + '0');
        i++;
    }
}

void timer_install()
{
    timer_phase(100);
    irq_install_handler(0, timer_handler);
}

void timer_wait(uint32_t ticks)
{
    uint64_t eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}

void timer_phase(uint32_t hz)
{
    uint32_t divisor = 1193180 / hz;       /* Calculate our divisor */
    outportb(0x43, 0x36);             /* Set our command byte 0x36 */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}