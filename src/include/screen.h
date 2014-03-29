#ifndef __SCREEN_H
#define __SCREEN_H

#include "stdint.h"

class screen
{
private:
	uint32_t place;
	uint32_t size;
	uint32_t offset;
	char lookup[16];
public:
	screen();
	void clear();
	void clear(uint8_t color);
	void puts(const char * str);
	void puts_nn(const char * str);
	void drop(uint32_t x, uint32_t y, char symbol);
	void puth(uint32_t num);
	void putc(uint8_t symbol);
};

#endif //__SCREEN_H
