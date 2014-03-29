#ifndef __TIMER_H
#define __TIMER_H

#include "types.h"
#include "inout.h"
#include "isr.h"

class timer{
public:
	timer(uint32_t freq);
	void callback(registers_t regs);
	uint64_t millis;
private:
	uint32_t div;
	uint8_t l, h;
	uint8_t *vid;
};

#endif //__TIMER_H