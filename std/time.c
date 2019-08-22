/**
   time.c, James Condron 2019

   Do some time munging stuff which is not device specific (like RTCs and so on)
**/

#include "time.h"
#include "printer.h"
#include "strings.h"
#include "../driver/rtc.h"

char *print_time_debug(struct t_time t, char *buffer) {
  char c[4];
  int i;

  i = cpy(0, buffer, "CMOS 0x0A: ");
  i = cpy(i, buffer, itoa(t.status_a, c, 10));
  i = cpy(i, buffer, " || CMOS 0x0B: ");
  i = cpy(i, buffer, itoa(t.status_b, c, 10));
  i = cpy(i, buffer, " || Additional Debug: ");
  i = cpy(i, buffer, t.debug);

  return buffer;
}

char *iso8601_ish(struct t_time t, char *buffer) {
  char c[4];
  int i;

  i = cpy(0, buffer, itoa(t.century, c, 10));
  i = cpy(i, buffer, itoa(t.year, c, 10));
  i = cpy(i, buffer, "-");
  i = cpy(i, buffer, itoa(t.month+1, c, 10));
  i = cpy(i, buffer, "-");
  i = cpy(i, buffer, itoa(t.day_of_month, c, 10));
  i = cpy(i, buffer, "T");
  i = cpy(i, buffer, itoa(t.hours, c, 10));
  i = cpy(i, buffer, ":");
  i = cpy(i, buffer, itoa(t.minutes, c, 10));
  i = cpy(i, buffer, ":");
  i = cpy(i, buffer, itoa(t.seconds, c, 10));
  i = cpy(i, buffer, t.zoneoffset);

  return buffer;
}

unsigned long bambitime() {
  return unixtime() - 578361600;
}
