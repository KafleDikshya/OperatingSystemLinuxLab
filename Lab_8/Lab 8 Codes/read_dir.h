#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>

#define MAXLENGTH 255 // for file names
#define BYTE 8

struct item_type 
{
   char name[MAXLENGTH];
   int count;
   struct item_type *next;
};

struct que_type
{
   struct item_type *head, *tail;
};

typedef struct que_type que_t;
typedef struct item_type item_t;

