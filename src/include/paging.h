#ifndef __PAGING_H
#define __PAGING_H

#include "resource.h"
#include "types.h"
#include "panic.h"

// the hunk starts here
#define hunk_start	0xD0000000
#define hunk_size	0x400000

class paging {
private:
	uint32_t *page_dir;
	uint32_t *page_table;		//for the id paging
	uint32_t *page_table2;		//for the first slab
	uint32_t *hunk;
	uint32_t address;
	void init_heap();
	uint32_t *map_first_slab(uint32_t pos, uint32_t size);
	bool have_heap;
	void *heap_top;
	void *slab_top;
	void add_slab();
public:
	paging();
	//number of bytes to id page
	void init(uint32_t bytes);
	void *map_slab(uint32_t pos, uint32_t bytes);
	void *dumb_kmalloc(size_t size);
};

#endif //__PAGING_H
