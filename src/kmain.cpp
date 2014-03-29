#include "include/stdint.h"
#include "include/screen.h"
#include "include/gdt.h"
#include "include/paging.h"
#include "include/idt.h"
#include "include/timer.h"
#include "include/resource.h"
#include "include/panic.h"
#include "include/sleep.h"

extern "C" void kmain(uint32_t stack_start)
{
	uint32_t magic;

	if ( magic != 0x2BADB002 ){
		//there was an error with the multiboot structure
		//error and halt
	}
	/* You could either use multiboot.h */
	/* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
	/* or do your offsets yourself. The following is merely an example. */
	//char * boot_loader_name =(char*) ((long*)mbd)[16];

	init_gdt();
	init_idt();

// 	__stack_chk_guard_setup();

// 	asm("hlt");

	//init the screen before pagging to handle panics
	//TODO fix the printing of panics so it works right(mabey has somthing to do with zeroed rodata???)
	screen tmp_screen;
	the_screen = &tmp_screen;

	the_screen->clear();

	paging kpage;
	kpage.init(0x400000);

	asm("sti");

// 	timer tmp_timer(1000);
// 	the_timer = &tmp_timer;


	char blaht[] = "blahblah";
// 	char *blahq = "hi there";

	the_screen->clear();

	//this will be the page directory
	uint32_t *ptr = (uint32_t *)kpage.dumb_kmalloc(sizeof(uint32_t));
	*ptr = 0x92;

// 	scarry_panic(blaht);

	
	the_screen->puts(blaht);
// 	the_screen->puth((uint32_t)blahq);
	the_screen->puth((uint32_t)blaht);
// 	sleep(20);

	the_screen->puth((uint32_t)ptr);
	the_screen->puth(*ptr);
	the_screen->puth(stack_start);

// 	broken function
/*	the_screen->putc('s');
	the_screen->putc('t');
	the_screen->putc('a');
	the_screen->putc('c');*/
// 	the_screen->puth((uint32_t)blahq[1]);
// 	the_screen->puth((uint32_t)blahq[2]);
// 	the_screen->puth((uint32_t)blahq[3]);
// 	the_screen->puth((uint32_t)blahq[4]);
	

// 	for(;;)
// 		;
	
// 	asm("int $0x3");
}