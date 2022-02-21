#include <limits.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <grp.h>
 #include <fcntl.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <sys/statvfs.h>
 #include <pwd.h>
 #include <time.h>
 #include <unistd.h>
 #include <limits.h>
 #include "read_dir.h"
 
 void process(char *name);
 void enqueue(char *name, que_t *q);
 void dequeue(que_t *q);
 void peek_front(char *name,que_t q);
 bool queue_empty(que_t q);
 void initq(que_t *q);

 int main(int argc,char *argv[]) {
   // main function
   if (2 != argc) {
     printf(" usage: %s dirpath\n", argv[0]);
     exit(-1);
   }
   else {
     // pass in the starting directory
     process(argv[1]);
   }

   return 0;
 }

 // traverse a directory tree applying a function when a file is found
 void process(char *root)
 {
   int num_reg_files = 0;
   int num_directories = 0;

   time_t least_recent_time = time(NULL);
   time_t most_recent_time = 0;
   char least_recent_file[MAXLENGTH];
   char most_recent_file[MAXLENGTH];

   off_t total_file_size = 0;
   off_t smallest_file = INT_MAX;
   off_t largest_file = 0;

   que_t nameq;
   char dname[MAXLENGTH];
   char cname[MAXLENGTH];
   char prefix[MAXLENGTH];

   struct dirent *dp;
   DIR *dirp;

   initq(&nameq);
   enqueue(root,&nameq);

   struct stat file_info;
   int file;


   while (true != queue_empty(nameq)) {
     peek_front(dname,nameq);
     dequeue(&nameq);
     dirp = opendir(dname);

     if (dirp != NULL) { // it is a directory

      printf("directory : %s\n",dname);
      strncpy(prefix, dname, MAXLENGTH);
      strncat(prefix,"/", MAXLENGTH);

       if (lstat(dname, &file_info)==0){
           if (S_ISLNK(file_info.st_mode)){
              printf("symbolic link: %s\n", dname);
           }

           else {

             	for (dp = readdir(dirp); NULL != dp; dp = readdir(dirp)) {
             	  if ((strcmp(dp->d_name,"..") != 0) &&
             	      (strcmp(dp->d_name,".") != 0)) {

             	    // prevent from infinite loop
             	    strncpy(cname, prefix, MAXLENGTH);

             	    // concatenate the prefix
             	    strncat(cname, dp->d_name, MAXLENGTH);
             	    enqueue(cname,&nameq);
            }
          }
     	  }
     	}
     	closedir (dirp);
      num_directories++;
    }

    else { 

      file = open(dname, O_RDONLY);
      if (-1 == file) {
        printf("  Not a regular file: %s\n", dname);
      }

      else {
	
           if (S_ISLNK(file_info.st_mode)){
              printf("symbolic link: %s\n", dname);
           }

        if (fstat(file, &file_info) == 0){

    	      if(file_info.st_size < smallest_file){
    		        smallest_file = file_info.st_size;
    	      }
    	      if(file_info.st_size > largest_file){
    		        largest_file = file_info.st_size;
    	      }

    	      total_file_size += file_info.st_size;
    	      num_reg_files++;

    	      if(file_info.st_mtime > most_recent_time){
            		strncpy(most_recent_file, dname, MAXLENGTH);
            		most_recent_time = file_info.st_mtime;
    	      }
    	      if(file_info.st_mtime < least_recent_time){
            		strncpy(least_recent_file, dname, MAXLENGTH);
            		least_recent_time = file_info.st_mtime;
    	      }
	      }
	      close(file);
	    }
    }
  }

  printf("Smallest file size: %d bytes\n", (int)smallest_file);
  printf("Largest file size: %d bytes\n", (int)largest_file);
  printf("Average file size: %d bytes\n", (int)total_file_size / num_reg_files);
  printf("Total number of directories: %d\n",num_directories);
  printf("The total number of regular files: %d\n",num_reg_files);
  printf("Most recently modified file: %s\n", most_recent_file);
  printf("Least recently modified file: %s\n", least_recent_file);

}

 // initialize queue data structure
 void initq(que_t *q) {
   q->head = q->tail = NULL;
 }

 // test whether queue data structure is empty
 bool queue_empty(que_t q) {
   if (NULL == q.head) {
      return true;
   } else {
     return false;
   }
 }

 // add an element to queue
 void enqueue(char *name, que_t *q) {
   item_t *temp;

   temp = (item_t *)malloc(sizeof(item_t));
   strncpy(temp->name,name,MAXLENGTH);
   temp->next = NULL;

   if (true == queue_empty(*q)) {
     q->head = temp;
     q->tail = temp;
   } else {
     q->tail->next = temp;
     q->tail = q->tail->next;
   }
 }

 // remove an element from the front of the queue
 void dequeue(que_t *q) {
   item_t *temp;

   if (true == queue_empty(*q)) {
     printf(" error in dequeue \n");
     exit(-1);
   } else {
     temp = q->head;
     q->head = q->head->next;
     free(temp);
   }
 }

 // find element at front of queue without removing
 void peek_front(char *name, que_t q) {
   if (true == queue_empty(q)) {
     printf(" error in dequeue \n");
      exit(-1);
   } else {
     strncpy(name, q.head->name, MAXLENGTH);
   }
 }

