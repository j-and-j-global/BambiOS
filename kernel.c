#include "kernel.h"
#include "driver/rtc.h"
#include "driver/keyboard.h"
#include "hardware/cmos.h"
#include "std/printer.h"
#include "std/time.h"
#include "std/strings.h"
#include "app/menu.h"

char *vidptr = (char*)0xb8000;  //video mem begins here.

unsigned int initialiser(int i, char *vidptr) {
  char tbuf[64];
  char disp = 0x08;

  i = printline(i, vidptr, "initialising...", disp);
  i = printline(i, vidptr, iso8601_ish(rtc(), tbuf), disp);
  i = printline(i, vidptr, print_time_debug(rtc(), tbuf), disp);

  return i;
}

void shutdown(void) {
  shutdown_message(vidptr);
  sleep(SLEEP_S);

  byebye();
}

void kmain(void) {
  while (!cmos_ready());

  unsigned int i = welcome(vidptr);
  i = initialiser(i, vidptr);

  sleep(SLEEP_S);

  cls(vidptr);
  menu_lines(0, 0, vidptr);

  idt_init();
  kb_init();

  while(1) {
    __asm__ __volatile__ ("hlt");
  }
}
