#include <stdlib.h>
#include "dnode.h"

struct dnode *dnode_create() {
	return calloc(1, sizeof(struct dnode));
}

void dnode_setdata(struct dnode *n, void *ptr,size_t size) {
	n->data = ptr;
    n->size = size;
}

void *dnode_destroy(struct dnode *n) {
	void *ptr = n->data;
	free(n);
	return ptr;
}

void dnode_obliterate(struct dnode *n) {
	free(n->data);
	free(n);
} 
