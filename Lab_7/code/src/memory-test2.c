#include "allocator.h"
#include "dnode.h"
#include "dlist.h"
#include <stdio.h>

void showMemory();
size_t blocks[] = {100,200,300,400,500};
void* ptrs[5];
void* ptr;
int main(int argv, char *argc[]){
    size_t size = 1500;
    printf("Calling allocator_init to initialize allocator and linked lists\n");
    allocator_init(size);
    showMemory();
    for(int i = 0; i<5;i++){
        printf("\nAllocate a block of size %zu using the best-fit method: ", blocks[i]);
        ptr = allocate(blocks[i],2);
        if(ptr==NULL){
            printf("Error, ptr is null\n");
        } else {
            printf("Success!\n");
            ptrs[i] = ptr;
        }
	showMemory();
    }
    printf("\nDeallocate node of size 100: ");
    int num = deallocate(ptrs[0]);
    if(num == 0) {
        printf("Success!\n");
    }
    showMemory();
    return 0;
}
void showMemory(){
	printf("Free List: ");
        showFreeList();
        printf("\nAllocated List: ");
        showAllocatedList();
        printf("\n");
}
