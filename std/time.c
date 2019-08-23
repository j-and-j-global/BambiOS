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

unsigned long bambitime(struct t_time time) {
  return unixtime(time) - 578361600;
}

unsigned long unixtime(struct t_time time) {
  char century = 20;
  if (time.century) {
    century = time.century;
  }

  int fullyear = time.year + (century * 100);
  int is_leapyear = leapyear(fullyear);

  unsigned long u = ((fullyear  - 1970) * YEAR_SECONDS);

  /* Add in all of the previous full years worth of leapday seconds */
  for (int year = 1970; year < fullyear; year++) {
    if (leapyear(year)) {
      u += DAY_SECONDS;
    }
  }

  /* Cover all of the full months of this year's worth of days so far */
  for (int month = 0; month < time.month; month++) {
    if (month == 2 && is_leapyear) {
      /* We've just ticked over the 29th February, add an extra day */
      u += DAY_SECONDS;
    }

    u += month_days(month) * DAY_SECONDS;
  }

  /* Tot up the rest of the days of this month, ignoring today */
  u += (time.day_of_month - 1) * DAY_SECONDS;

  /* Add todays hours */
  u += (time.hours) * HOUR_SECONDS;

  /* Add the minutes of this hour */
  int minutes = time.minutes;
  if (minutes == 0) {
    minutes = 60;
  }

  u += (minutes * MINUTE_SECONDS);

  /* Finally, add the current set of seconds and return */
  u += time.seconds;

  return u;
}

void sleep(int seconds) {
  struct t_time time = rtc();

  unsigned long now = bambitime(time);
  unsigned long until = now + seconds;

  do {
    time = rtc();
  } while (bambitime(time) < until) ;
}
