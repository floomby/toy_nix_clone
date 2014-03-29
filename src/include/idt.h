#ifndef __IDT_H
#define __IDT_H

#include "types.h"
#include "gdt.h"
#include "mem.h"
#include "inout.h"

struct idt_entry_struct {
	uint16_t	base_lo;
	uint16_t	sel;
	uint8_t		always0;
	uint8_t		flags;
	uint16_t	base_hi;
} __attribute__ ((packed));

typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct {
	uint16_t	limit;
	uint32_t	base;
}  __attribute__ ((packed));

typedef struct idt_ptr_struct idt_ptr_t;

void init_idt();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

extern "C" {
extern void idt_flush(uint32_t);
extern uint32_t isr0();
extern uint32_t isr1();
extern uint32_t isr2();
extern uint32_t isr3();
extern uint32_t isr4();
extern uint32_t isr5();
extern uint32_t isr6();
extern uint32_t isr7();
extern uint32_t isr8();
extern uint32_t isr9();
extern uint32_t isr10();
extern uint32_t isr11();
extern uint32_t isr12();
extern uint32_t isr13();
extern uint32_t isr14();
extern uint32_t isr15();
extern uint32_t isr16();
extern uint32_t isr17();
extern uint32_t isr18();
extern uint32_t isr19();
extern uint32_t isr20();
extern uint32_t isr21();
extern uint32_t isr22();
extern uint32_t isr23();
extern uint32_t isr24();
extern uint32_t isr25();
extern uint32_t isr26();
extern uint32_t isr27();
extern uint32_t isr28();
extern uint32_t isr29();
extern uint32_t isr30();
extern uint32_t isr31();

extern uint32_t irq0();
}

#endif //__IDT_H