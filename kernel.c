#include "kernel.h"
#include "driver/rtc.h"
#include "hardware/cmos.h"
#include "std/printer.h"
#include "std/time.h"
#include "std/strings.h"
#include "app/menu.h"

unsigned int initialiser(int i, char *vidptr) {
  char tbuf[64];
  char disp = 0x08;

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

  sleep(SLEEP_S);

  cls(vidptr);
  menu_lines(3, vidptr);

  sleep(1);
  menu_lines(4, vidptr);

  sleep(1);
  menu_lines(5, vidptr);

  sleep(1);
  menu_lines(4, vidptr);
}
