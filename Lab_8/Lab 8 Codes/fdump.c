#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "hexdump.h"
int main(int argc, char *argv[]){
  
  unsigned int offset;
  unsigned int size;
  
  if(argc != 4){
    printf("Invalid number of parameters, must be in for of [filename] [offset] [size]\n");
    return -1;
  }
  
  sscanf(argv[2], "%d", &offset);
  sscanf(argv[3], "%d", &size);

  FILE *fp;
    if ((fp = fopen(argv[1], "rb")) == NULL)
    {
        printf("Fail to open file!\n");
        exit(0);
    }
  
  unsigned char buffer[size+1];
  fseek(fp, (long)offset, SEEK_SET);
  fread(buffer,sizeof(char),size,fp);
  
  hexdump(buffer, size+1);
  fclose(fp);
  printf("\n");

  return 0;
}


