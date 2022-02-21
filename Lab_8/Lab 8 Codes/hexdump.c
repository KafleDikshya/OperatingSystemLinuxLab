#include <stdio.h>

char is_printable(unsigned char c) {
     if ((c >= 0x20) && (c < 0x7F))
	  return c;
     else
	  return '.';
}

void hexdump(unsigned char* buffer, unsigned int length) {
     int b=0, c=0;
     int s, rem;
     
     // b is a counter for the number of bytes (half the number of hex digits)

     printf("\n     PAYLOAD HEXDUMP:\n");
     while (b < length) {
	  printf("\n     %07x:", b);
	  for (; (b%16<15) && (b<length); b++) {
	       if (0 == b % 2)
		    printf(" ");
	       printf("%02hhx", buffer[b]);
	  }

	  if (b < length)
	       printf("%02hhx   ",  buffer[b++]);
	  else { // print a number of spaces to align the remaining text
	       rem = b % 16;
	       for (s=0; s < 44 - ((rem*2) + (rem/2) + 1); s++)
		    printf(" ");
	  }

	  for (;(c%16<15) && (c<length); c++) {
	       printf("%c", is_printable(buffer[c]));
	  }
	  if (c<length)
	       printf("%c", is_printable(buffer[c++]));
     }
     printf("\n");
}
