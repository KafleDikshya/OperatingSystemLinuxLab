#include "allocator.h"
#include "dnode.h"
#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char *policy[] = {"first-fit", "best-fit", "worst-fit"};
    size_t size = 1024*1024;
    allocator_init(size);
    int algorithm = atoi(argv[1]);
    srand(atoi(argv[2]));
    int requests = atoi(argv[3]);
    int r = 0;
    void *p = NULL;
    while(r<requests){
        long s = (random()+100)%10000;
        p = allocate(s,algorithm);
        deallocate(p);
        r++;
    }
    double fragmentation = average_frag();
    printf("Average fragmentation using %s with %d requests is %f\n", policy[algorithm],requests,fragmentation);     
    return 0;

}
