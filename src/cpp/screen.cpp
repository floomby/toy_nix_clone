#include "../include/screen.h"

screen::screen()
{
	place = 0xb8000;
	size = (80*25)*2;	//80 charecters by 25 charecter by 2 bytes per charecter
	offset = 0;

	lookup[0]  = '0';
	lookup[1]  = '1';
	lookup[2]  = '2';
	lookup[3]  = '3';
	lookup[4]  = '4';
	lookup[5]  = '5';
	lookup[6]  = '6';
	lookup[7]  = '7';
	lookup[8]  = '8';
	lookup[9]  = '9';
	lookup[10]  = 'A';
	lookup[11]  = 'B';
	lookup[12]  = 'C';
	lookup[13]  = 'D';
	lookup[14]  = 'E';
	lookup[15]  = 'F';
}

void screen::clear()
{
	for(uint32_t i = 0; i < size; i += 2){
		((uint8_t *)place)[i] = 0x20;	//space
		((uint8_t *)place)[i+1] = 0x07;
	}

	offset = 0;
}

void screen::clear(uint8_t color)
{
	for(uint32_t i = 0; i < size; i += 2){
		((uint8_t *)place)[i] = 0x20;	//space
		((uint8_t *)place)[i+1] = color;
	}

	offset = 0;
}

//does not handle newlines yet
void screen::puts(const char * str)
{
	for(uint32_t i = (offset*2); *str; str++, i += 2, offset++)
		*((uint8_t *)(place+i)) = *str;

	offset += 80 - (offset%80);
}

void screen::puts_nn(const char * str)
{
	for(uint32_t i = (offset*2); *str; str++, i += 2, offset++)
		*((uint8_t *)(place+i)) = *str;
}

void screen::puth(uint32_t num)
{
	uint32_t mask = 0xF0000000;
	char tmp[11];

	tmp[0] = '0';
	tmp[1] = 'x';

	for(uint32_t i = 0; i < 8; i++){
		tmp[2+i] = lookup[((num & mask) >> (28 - 4*i))];
		mask >>= 4;
	}

	tmp[11] = '\0';
	this->puts(tmp);
}

void screen::drop(uint32_t x, uint32_t y, char symbol)
{
	x *= 2;
	y *= 2;

	((uint8_t *)place)[y*80 + x] = symbol;
}

void screen::putc(uint8_t symbol)
{
	*((uint8_t *)(place+offset*2)) = symbol;
	offset++;
}












