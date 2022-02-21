#include "buffer.h"

Buffer_item buffer[BUFFER_SIZE];

int counter;

int insert_item(Buffer_item item) {

   if(counter < BUFFER_SIZE) {

      buffer[counter] = item;

      counter++;

      return 0;

   }

   else { 

    //buffer is full

      return -1;

   }

}

int remove_item(Buffer_item *item) {

   if(counter > 0) {

      *item = buffer[(counter-1)];

      counter--;

      return 0;

   }

   else { 

      //buffer empty

      return -1;

   }



}
