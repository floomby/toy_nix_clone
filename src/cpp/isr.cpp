#include "../include/isr.h"

extern "C" {
void isr_handler(registers_t regs)
{
	volatile unsigned char *videoram = (unsigned char *)0xB8000;
	videoram[0] = 65 + regs.int_no; /* character 'A' */
	videoram[1] = 0x07; /* light grey (7) on black (0). */
}

static isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
	// Send an EOI (end of interrupt) signal to the PICs.
	// If this interrupt involved the slave.
	if (regs.int_no >= 40){
		// Send reset signal to slave.
		outb(0xA0, 0x20);
	}
	// Send reset signal to master. (As well as slave, if necessary).
	outb(0x20, 0x20);

	if (interrupt_handlers[regs.int_no] != 0){
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}

}