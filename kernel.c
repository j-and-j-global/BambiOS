#include "kernel.h"
#include "driver/rtc.h"
#include "hardware/cmos.h"
#include "std/printer.h"
#include "std/time.h"
#include "std/strings.h"

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

unsigned int initialiser(int i, char *vidptr) {
  char tbuf[64];
  char disp = 0x08;

  i = printline(i, vidptr, emptyLine, 0x01);
  i = printline(i, vidptr, "initialising...", disp);
  i = printline(i, vidptr, iso8601_ish(rtc(), tbuf), disp);
  i = printline(i, vidptr, print_time_debug(rtc(), tbuf), disp);

  return i;
}

void kmain(void) {
  while (!cmos_ready());

  char *vidptr = (char*)0xb8000;  //video mem begins here.

  unsigned int i = welcome(vidptr);
  i = initialiser(i, vidptr);
  i = startup(i, vidptr);
}
