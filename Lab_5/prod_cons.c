#include <stdlib.h>

#include <stdio.h>

#include <unistd.h>

#include <pthread.h>

#include <semaphore.h>

#include "buffer.h"



#define DIVISOR 100000000



pthread_mutex_t mutex;

sem_t full, empty;



pthread_t tid; 

pthread_attr_t attr;



void *producer(void *param); 

void *consumer(void *param); 





int main(int argc, char *argv[]) {



   if(argc != 4) {

      fprintf(stderr, "USAGE:.Prod_com [num_prod] [num_cons] [sleep_time]\n");

   }



   int i;

   int NProd = atoi(argv[1]); 

   int NCons = atoi(argv[2]);

   int mainSleepTime = atoi(argv[3]);





   pthread_mutex_init(&mutex, NULL);

   sem_init(&full, 0, 0);

   sem_init(&empty, 0, BUFFER_SIZE);

   pthread_attr_init(&attr);

   counter = 0;



   //Create the producers

   for(i = 0; i < NProd; i++) {

      pthread_create(&tid,&attr,producer,NULL);

    }





   //Create the consumers

   for(i = 0; i < NCons; i++) {

      pthread_create(&tid,&attr,consumer,NULL);

   }



   //main fucntion sleep

   sleep(mainSleepTime);



   return 0;

}







//Producer Thread

void *producer(void *param) {

   

   Buffer_item item;



   while(1) {

      //sleep

      int rNum = rand() / DIVISOR;

      sleep(rNum);



      item = rand();



      sem_wait(&empty);

      pthread_mutex_lock(&mutex);



      if(insert_item(item)) {

         fprintf(stderr, "Producer reported an error while inserting\n");

      }

      else {

         printf("producer produced %d\n", item);

      }



      pthread_mutex_unlock(&mutex);

      sem_post(&full);

   }

}



//Consumer Thread 

void *consumer(void *param) {

   Buffer_item item;



   while(1) {

      /* sleep for a random period of time */

      int rNum = rand() / DIVISOR;

      sleep(rNum);



      sem_wait(&full);

      pthread_mutex_lock(&mutex);

      

      if(remove_item(&item)) {

         fprintf(stderr, "Consumer reported an error while removing\n");

      }

      else {

         printf("consumer consumed %d\n", item);

      }

      

      pthread_mutex_unlock(&mutex);

      sem_post(&empty);

   }

}




