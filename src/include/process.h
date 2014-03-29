#ifndef __PROCESS_H
#define __PROCESS_H

#include "isr.h"

typedef struct _process {
	registers_t regs;
	uint32_t stack_start;
	uint32_t status;
	char name[64];
} process;







#endif //__PROCESS_H