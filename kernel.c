#include "kernel.h"
#include "driver/rtc.h"
#include "hardware/cmos.h"
#include "std/printer.h"

void welcome(char* vidptr) {
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

  i = printline(i, vidptr, emptyLine, 0x01);

  i = printline(i, vidptr, ltoa_bt(unixtime()), 0x4f);
  i = printline(i, vidptr, pressEnter, 0x05);
}

void kmain(void) {
  while (!cmos_ready());

  char *vidptr = (char*)0xb8000;  //video mem begins here.

  welcome(vidptr);
}
