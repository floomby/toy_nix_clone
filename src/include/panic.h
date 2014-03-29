#ifndef __PANIC_H
#define __PANIC_H

#include "resource.h"
#include "types.h"

void panic(const char *msg);
void scarry_panic(const char *msg);

#endif //__PANIC_H