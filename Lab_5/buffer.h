#ifndef _BUFFER_H_

#define _BUFFER_H_



#define BUFFER_SIZE 5

typedef int Buffer_item;



/* the buffer */

extern Buffer_item buffer[BUFFER_SIZE];



/* buffer counter */

extern int counter;





int insert_item(Buffer_item item);

int remove_item(Buffer_item *item);



#endif

