#include "kernel.h"
#include "print.h"

void welcome(char* vidptr) {
  char *emptyLine = "                                                                                ";

  unsigned int i = 0;

  while(i < COLS * LINES * 2) {
    vidptr[i] = ' ';
    vidptr[i+1] = 0x07;
    i = i + 2;
  }

  i = printline(0, vidptr, welcomeMessage, 0x05);
  i = printline(i, vidptr, copyright, 0x03);
  i = printline(i, vidptr, emptyLine, 0x01);
  i = printline(i, vidptr, booting, 0x4f);
}

void kmain(void) {
  char *vidptr = (char*)0xb8000;  //video mem begins here.

  welcome(vidptr);
}
