#include "dlist.h"
#include "dnode.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
struct dlist *free_list;
struct dlist *allocated_list;

int allocator_init(size_t size){
    void *data;
    struct dnode *node;
    if((data=malloc(size))==NULL){
        return -1;
    }
    node = dnode_create();
    dnode_setdata(node,data,size);

    free_list = dlist_create();
    dlist_add_front(free_list,node,size);
    allocated_list = dlist_create();
    return 0;
}

void* allocateFirstFit(size_t size){
    void* curr = dlist_iter_begin(free_list);
    int i = 0;
    while(i < free_list->counter) {
        if(free_list->iter->size >= size) {
            //size of current node can fit the node we want to allocate
            //allocate space in this spot
            return curr;
        }
        curr = dlist_iter_begin(free_list);
        i++;
    }
    return NULL;
 }

void* allocateBestFit(size_t size){
    void *curr;
    void* best;
    size_t min = 0;
    int i = 0;

    curr = dlist_iter_begin(free_list);
    while(i < free_list->counter) {
        if(free_list->iter->size >= size) {
            if(free_list->iter->size < min && min!=0) {
                min = free_list->iter->size;
                best = curr;
            } else if(min==0) {
                min = free_list->iter->size;
                best = curr;
            }
        } 
        curr = dlist_iter_next(free_list);
        i++;
    }

    if(min==0){
        return NULL;
    }else{
        return best;
    }

}

void* allocateWorstFit(size_t size){
     void *curr;
     void *worst;
     size_t max = 0;
     int i = 0;

     curr = dlist_iter_begin(free_list);
     while(i < free_list->counter) {
         if(free_list->iter->size >= size && free_list->iter->size > max) {
             worst = curr;
             max = free_list->iter->size;
         }
         i++;
     }
     if(max==0){
         return NULL;
     } else {
         return worst;
     }
}


int deallocate(void *ptr){
    void *curr;
    curr = dlist_iter_begin(allocated_list);
    for(int i = 0; i< allocated_list->counter;i++) {
        if(curr==ptr){
            size_t size = allocated_list->iter->size;
            dlist_add_back(free_list,curr,size);
            curr = dlist_find_remove(allocated_list, ptr);
            return 0;
        }
        curr = dlist_iter_next(allocated_list);
    }
    return -1;
}

void *allocate(size_t size, int policy){
    void* ptr;
    void* curr;
    if(policy == 0){
       ptr = allocateFirstFit(size);
    }
    else if(policy == 1){
        ptr = allocateBestFit(size); 
    }
    else if(policy == 2){
        ptr = allocateWorstFit(size);
    }else{
    	printf("Error in allocate, wrong policy number!\n");
    }
    if(ptr == NULL){
    	//comment this line when observing fragmentation - It is expected to not being able to allocated memory to processes due to fragmentation
        //printf("Error in allocate\n");
        return NULL;
    }

    curr = dlist_iter_begin(free_list);
    int i = 0;
    while(i < free_list->counter){
        if(ptr == curr) {
            free_list->iter->size -= size;
            free_list->iter->data += size;
            break;
        }
        curr = dlist_iter_next(free_list);
        i++;
    }
    dlist_add_back(allocated_list,ptr,size);
    return ptr;
}

void showFreeList(){
    dlist_iter_begin(free_list);
    for(int i = 0; i< free_list->counter;i++) {
	size_t size = free_list->iter->size;
	printf("%zu ",size);
        dlist_iter_next(free_list);
    }
}

void showAllocatedList(){
    dlist_iter_begin(allocated_list);
    for(int i = 0; i< allocated_list->counter;i++) {
	size_t size = allocated_list->iter->size;
	printf("%zu ",size);
        dlist_iter_next(allocated_list);
    }
}

double average_frag() {
    size_t sum = 0;
    dlist_iter_begin(free_list);
    int i = 0;
    while(i < free_list->counter){
        sum += free_list->iter->size;
        dlist_iter_next(free_list);
        i++;
    }
    return sum/(free_list->counter);
}

