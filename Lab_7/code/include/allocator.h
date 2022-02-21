#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*
initialize allocated and free list
*/

int allocator_init(size_t size);

/*
malloc()
*/

void *allocate(size_t size, int policy);

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

/*
Compute the average fragmentation
*/
double average_frag();

#endif /* _ALLOCATOR_H_ */
