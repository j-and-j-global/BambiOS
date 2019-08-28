#include "kernel.h"
#include "buffer.h"
#include "std/printer.h"

unsigned int welcome(char* vidptr) {
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

  return i;
}

unsigned int startup(int i, char *vidptr) {
  i = printline(i, vidptr, emptyLine, 0x01);
  i = printline(i, vidptr, pressEnter, 0x05);

  return i;
}

unsigned int dummy(char *vidptr) {
  return printline(0, vidptr, "JAMES IS SEXY", 0x3C);
}

void cls(char *vidptr) {
  int pos = 0;

  for (int i = 0; i <= LINES; i++) {
    pos = printline(pos, vidptr, emptyLine, 0x01);
  }
}

unsigned int shutdown_message(char *vidptr) {
  cls(vidptr);

  int i = 0;
  i = printline(i, vidptr, goodbyeMessage, 0x05);
  i = printline(i, vidptr, copyright, 0x03);
  i = printline(i, vidptr, emptyLine, 0x01);
  i = printline(i, vidptr, shuttingDown, 0x4f);

  return i;
}
