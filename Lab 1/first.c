  
#include <stdio.h>
#include <stdlib.h>

int var1;            /* a staticly allocated variable */

int my_func(int i) {      
    int j = i;            
    printf("my_func call %ld: stack@ %ld\n", &i, &j);
    if (i > 0) {
        return my_func(i-1);
    }
    return 0;
}

 /* a statically allocarted, pre-initialized variable */
volatile int stuff = 7;         

int main (int argc, char *argv[]) {
    
    /* a stack allocated variable */
    volatile int i;    
    /* dynamically allocate some stuff */        
    volatile char *buf1 = malloc(100); 
     /* and some more stuff */
    volatile char *buf2 = malloc(100);
    
    printf("_main  @ %p\n", main); /* fix to print address of main */
    printf("my_func @ %p\n", my_func); /* fix to print address of my_func */
    printf("_main stack: %ls\n", &i); /* fix to get address of the stack variable */
    printf("static data: %ls\n", &stuff); /* fix to get address of a static variable */
    printf("Heap: malloc 1: %ld\n", (long unsigned int) buf1);
    printf("Heap: malloc 2: %ld\n", (long unsigned int) buf2);
    
    my_func(3);

    return 0;
}
