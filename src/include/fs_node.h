#ifndef __FS_NODE_H
#define __FS_NODE_H

#include "types.h"

class fs_node {
public:
	const char *name;
private:
	char name_buf[128];
	
};

#endif //__FS_NODE_H