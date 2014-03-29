#include "../include/paging.h"

//TODO consider moving entire paging structure into high memory

paging::paging()
{
	page_dir = (uint32_t *)0x9C000;
	page_table = (uint32_t *)0x9D000;
	page_table2 = (uint32_t *)0x9E000;
	//still have 0x9F000
	address = 0x0;
	have_heap = false;
}

void paging::init(uint32_t bytes)
{
	register uint32_t i;

	if(bytes > 0x400000){
		char msg[] = "PANIC: attempted to id page more that 4MB(not supported)";
		panic(msg);
	}

	bytes /= 4096;

	for(i = 0; i < bytes; i++){
		page_table[i] = address | 3; // attribute set to: supervisor level, read/write, present(011 in binary)
		address += 4096 ;
	}

	// fill the first entry of the page directory
	page_dir[0] = (uint32_t)page_table; // attribute set to: supervisor level, read/write, present(011 in binary)
	page_dir[0] = page_dir[0] | 3;  // +1024 means "page table in use"
	for(i=1; i<1024; i++){
		page_dir[i] = 0 | 2; // attribute set to: supervisor level, read/write, present(011 in binary)
	};

	asm volatile("mov %0, %%cr3":: "r"(page_dir));
	uint32_t cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

void paging::init_heap()
{
	hunk = this->map_first_slab(hunk_start, hunk_size);
	have_heap = true;
	heap_top = (void *)0xD0400000;
	slab_top = (void *)0xD0400000;
}

uint32_t *paging::map_first_slab(uint32_t pos, uint32_t bytes)
{
	register uint32_t i;

	bytes /= 4096;

	uint32_t dir_num = pos / 0x400000;

	for(i = 0; i < bytes; i++){
		page_table2[i] = address | 3; // attribute set to: supervisor level, read/write, present(011 in binary)
		address += 4096;
	}
	page_dir[dir_num] = (uint32_t)page_table2;
	page_dir[dir_num] |= 3;

	return (uint32_t *)pos;
}

void *paging::map_slab(uint32_t pos, uint32_t bytes)
{
	register uint32_t i;

	if(!have_heap)
		this->init_heap();

	if(bytes > 0x400000){
		char msg[] = "PANIC: attempted to map a slab more that 4MB(not supported)";
		panic(msg);
	}

	bytes /= 4096;

	uint32_t dir_num = pos / 0x400000;

	for(i = 0; i < bytes; i++){
		*(hunk + dir_num*1024) = address | 3; // attribute set to: supervisor level, read/write, present(011 in binary)
		address += 4096;
	}
	page_dir[dir_num] = uint32_t(hunk + dir_num*1024);
	page_dir[dir_num] |= 3;

	return (void *)pos;
}

void paging::add_slab()
{
	this->map_slab((uint32_t)slab_top, 0x400000);
	slab_top = (void *)((uint32_t)slab_top + 0x400000);
}

void *paging::dumb_kmalloc(size_t size)
{
	if(!have_heap)
		this->init_heap();

	if(heap_top >= slab_top){
		this->add_slab();
	}

	void *tmp = heap_top;
	heap_top = (void *)((uint32_t)heap_top + 0x400000);

	return tmp;
}