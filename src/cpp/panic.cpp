#include "../include/panic.h"

void panic(const char *msg)
{
	the_screen->puts(msg);

	asm("cli");
	asm("hlt");
}

void scarry_panic(const char *msg)
{
	the_screen->clear(0x17);
	the_screen->puts(msg);

	asm("cli");
	asm("hlt");
}