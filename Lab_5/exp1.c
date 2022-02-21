#include<stdio.h>

#include<string.h>

#include<pthread.h>

#include<stdlib.h>

#include<unistd.h>

#include<semaphore.h>

#include<sys/types.h>





pthread_t tid[2];

int counter;

sem_t mutex;

void* doSomeThing(void *arg)

{

    if(pthread_self()== tid[1])

    	sem_wait(&mutex);

    	

    unsigned long i = 0;

    counter += 1;

    		printf("\n Job %d started by %d\n", counter,gettid());

    for(i=0; i<1000;i++);

    		printf("\n Job %d finished by %d\n", counter,gettid());

    

    if(pthread_self()== tid[0])

    	sem_post(&mutex);

    return NULL;

}



int main(void)

{

    int i = 0;

    int err;

    

    sem_init(&mutex,0,0);

    

    while(i < 2)

    {

        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);

        if (err != 0)

            printf("\ncan't create thread :[%s]", strerror(err));

        i++;

    }



    pthread_join(tid[0], NULL);

    pthread_join(tid[1], NULL);

    sem_destroy(&mutex);

    return 0;

}
