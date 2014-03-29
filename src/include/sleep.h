#ifndef __SLEEP_H
#define __SLEEP_H

#include "types.h"
#include "resource.h"

void msleep(uint64_t micros);
void sleep(uint32_t sec);

#endif //__SLEEP_H