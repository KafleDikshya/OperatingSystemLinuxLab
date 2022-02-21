#include<stdio.h>



#include<string.h>



#include<pthread.h>



#include<stdlib.h>



#include<unistd.h>







pthread_t tid[2];



int counter;



pthread_mutex_t mutex;







void* doSomeThing(void *arg)



{



    pthread_mutex_lock(&mutex);



    long i = 0;



    counter +=1;



    		printf("\n Job %d started\n", counter);



    for(i=0; i<1000000;i++);



    		printf("\n Job %d finished\n", counter);



    		pthread_mutex_unlock(&mutex);



    return NULL;



}







int main(void)



{



    int i = 0;



    int err;



    



    if (pthread_mutex_init(&mutex, NULL) !=0)



    {



            printf("\n can't create thread :[%s]", strerror(err));



            return 1;



    }



    



    while (i < 2)



    {



    err = pthread_create(&(tid[1]), NULL, &doSomeThing, NULL);



        if (err != 0)



            printf("\n can't create thread :[%s]", strerror(err));



        i++;



    }







    pthread_join(tid[0], NULL);



    pthread_join(tid[1], NULL);



    pthread_mutex_destroy(&mutex);



    return 0;



}
