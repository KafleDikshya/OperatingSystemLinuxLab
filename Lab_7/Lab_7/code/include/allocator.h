#include <stdint.h>
#include <stdbool.h>
#include "dnode.h"
#include "dlist.h"

/*
initialize allocated and free list
*/
int allocator_init(size_t size, int typee);

/*
malloc()
*/
void* allocate(size_t size);

/*
free()
*/
int deallocate(void *ptr);

/*
Use First-Fit policy
*/
void* allocateFirstFit(size_t size);

/*
Use Best-Fit policy
*/
void* allocateBestFit(size_t size);

/*
Use Worst-Fit policy
*/
void* allocateWorstFit(size_t size);

/*
Show state of free-list
*/
void showFreeList();

/*
Show state of allocated-list
*/
void showAllocatedList();
