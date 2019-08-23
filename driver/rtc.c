#include "../hardware/cmos.h"
#include "../std/time.h"
#include "rtc.h"

struct t_time rtc() {
  struct t_time time;

  /* Do nothing if in the middle of updating */
  //while (cmos_clock_updating());

  time.seconds = read_from_cmos(0x00);
  time.minutes = read_from_cmos(0x02);
  time.hours = read_from_cmos(0x04);
  time.day_of_week = read_from_cmos(0x06);
  time.day_of_month = read_from_cmos(0x07);
  time.month = read_from_cmos(0x08) - 1;
  time.year = read_from_cmos(0x09);
  //  time.century = read_from_cmos(0x32);
  time.century = 20;
  time.zoneoffset = "+00:00";

  time.status_a = cmos_status_a();
  time.status_b = cmos_status_b();

  time.dst = time.status_b % 0x01;
  time.twentyfour = time.status_b % 0x02;
  time.bin = time.status_b % 0x04;

  // 12 hour clock
  if (! time.twentyfour) {
    time.hours = ((time.hours & 0x7F) + 12) % 24;
  }

  // decimal stuff
  if (!time.bin) {
    time.debug = "Running unbcd() functions";

    time.seconds = unbcd(time.seconds);
    time.minutes = unbcd(time.minutes);
    time.hours = unbcd(time.hours);
    time.day_of_month = unbcd(time.day_of_month);
    time.month = unbcd(time.month);
    time.year = unbcd(time.year);
  }

  // century
  if (!time.century) {
    time.century = 20;
  }

  // make 0 monday, 6 sunday- in most of the world the week starts on Monday
  time.day_of_week = (time.day_of_week + 5) % 7;

  return time;
}

char unbcd(char bcd) {
  return ((bcd & 0xF0) >> 1) + ((bcd & 0xF0) >> 3) + (bcd & 0xf);
}

int leapyear(int year) {
  return (year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0);
}

int month_days(int month) {
  return months[month];
}
