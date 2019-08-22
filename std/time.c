/**
   time.c, James Condron 2019

   Do some time munging stuff which is not device specific (like RTCs and so on)
**/

#include "time.h"
#include "printer.h"
#include "strings.h"

char *iso8601_ish(struct t_time t, char *buffer) {
  char c[4];
  int i;

  i = cpy(0, buffer, itoa(t.century, c, 10));
  i = cpy(i, buffer, itoa(t.year, c, 10));
  i = cpy(i, buffer, "-");
  i = cpy(i, buffer, itoa(t.month, c, 10));
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
