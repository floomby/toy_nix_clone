#include "../include/timer.h"

static timer *mytimer;
static void pit_callback(registers_t regs);

timer::timer(uint32_t freq)
{
	millis = 0;

	register_interrupt_handler(IRQ0, &pit_callback);

	div = 1193180 / freq;
	outb(0x43, 0x36);

	l = (uint8_t)(div & 0xFF);
	h = (uint8_t)((div >> 8) & 0xFF );

	outb(0x40, l);
	outb(0x40, h);

	vid = (uint8_t *)0xB8000;

	mytimer = this;
}

void timer::callback(registers_t regs)
{
	millis++;
}

static void pit_callback(registers_t regs)
{
	mytimer->callback(regs);
}
