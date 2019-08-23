#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "std/printer.h"
#include "std/time.h"
#include "std/strings.h"
#include "driver/rtc.h"

int test_rtc() {
  printf("test_rtc()\n");

  struct t_time r = rtc();

  if (r.seconds != 1) {
    printf("\tseconds: expected 1, received %d\n", r.seconds);

    return 1;
  }

  if (r.minutes != 30) {
    printf("\tminutes: expected 30, received %d\n", r.minutes);

    return 1;
  }

  if (r.hours != 16) {
    printf("\thours: expected 16, received %d\n", r.hours);

    return 1;
  }

  if (r.day_of_week != 2) {
    printf("\tday_of_week: expected 2, received %d\n", r.day_of_week);

    return 1;
  }

  if (r.day_of_month != 21) {
    printf("\tday_of_month: expected 21, received %d\n", r.day_of_month);

    return 1;
  }

  if (r.month != 7) {
    printf("\tmonth: expected 7, received %d\n", r.month);

    return 1;
  }

  if (r.year != 19) {
    printf("\tyear: expected 19, received %d\n", r.year);

    return 1;
  }

  if (r.century != 20) {
    printf("\tcentury: expected 20, received %d\n", r.century);

    return 1;
  }

  if (r.twentyfour != 1) {
    printf("\ttwentyfour: expected 1, received %d\n", r.twentyfour);

    return 1;
  }

  if (r.dst != 0) {
    printf("\tdst: expected 0, received %d\n", r.dst);

    return 1;
  }

  if (r.bin != 3) {
    printf("\tbin: expected 3, received %d\n", r.bin);

    return 1;
  }

  return 0;
}

int test_unixtime() {
  printf("test_unixtime()\n");

  struct t_time rtc_time = rtc();
  unsigned long t = unixtime(rtc_time);

  if (t != 1566405001) {
    printf("\tunixtime(): expected 1566405001, received %lu\n", t);

    return 1;
  }

  return 0;
}

int test_spacecount() {
  printf("test_spacecount()\n");

  // if our message is "hello, world!", then:
  //   * Our message its self is 13 chars; but
  //   * we're using 26 chars of video memory (one char for content, another for display)
  //
  // Thus: with our max width being 80, we expect to be told to pad with 67 spaces (again)

  int spaces = spacecount(26);

  if (spaces != 67) {
    printf("\tspacecount(): expected 67, received %d\n", spaces);

    return 1;
  }

  return 0;
}

int test_spacecount2() {
  printf("test_spacecount2()\n");

  // if our message is "another line!", and is the second line, then:
  //   * Our message its self is 13 chars; but
  //   * we're using 26 chars of video memory (one char for content, another for display)
  //   * our memory location is 186 - the 160 of the first line, plus the 26 of this
  //
  // Thus: with our max width being 80, we expect to be told to pad with 67 spaces

  int spaces = spacecount(186);

  if (spaces != 67) {
    printf("\tspacecount(): expected 67, received %d\n", spaces);

    return 1;
  }

  return 0;
}

int test_ltoa_bt() {
  printf("test_ltoa_bt()\n");

  char buffer[33];
  char *s = ltoa_bt(1566421075, buffer);
  char *expect = "1566421075";

  if (strcmp(s, expect) != 0) {
    printf("\tltoa_bt(): expected %s, received %s\n", expect, s);

    return 1;
  }

  return 0;
}

int test_itoa() {
  printf("test_itoa()\n");

  char buffer[33];
  const char *s = itoa(123, buffer, 10);
  const char *expect = "123";

  if (strcmp(s, expect) != 0) {
    printf("\titoa(): expected %s, received %s\n", expect, s);

    return 1;
  }

  return 0;
}

int test_iso8601_ish() {
  printf("test_iso8601_ish()\n");

  struct t_time r = rtc();
  char buffer[33];
  const char *s = iso8601_ish(r, buffer);
  const char *expect = "2019-8-21T16:30:1+00:00";

  if (strcmp(s, expect) != 0) {
    printf("\tiso8601_ish(): expected %s, received %s\n", expect, s);

    return 1;
  }

  return 0;
}

int test_cpy() {
  printf("test_cpy\n");

  char buffer[32];
  char *a = "Hello, ";
  char *b = "World!";
  char *expect = "Hello, World!";

  int pos;

  pos = cpy(0, buffer, a);
  pos = cpy(pos, buffer, b);

  if (strcmp(buffer, expect) != 0) {
    printf("\tcpy(): expected %s, received %s\n", expect, a);

    return 1;
  }

  if (pos != 13) {
    printf("\tposition should be 13, is %d\n", pos);

    return 1;
  }

  return 0;
}

int null() {
  return 0;
}

int main(void) {
  const int tests = 8;

  int (*p[8]) () = {
    test_rtc, test_unixtime, test_spacecount, test_spacecount2, test_ltoa_bt, test_itoa, test_iso8601_ish, test_cpy,
  };

  int ret;
  int errs = 0;

  for (int i = 0; i < tests; i++) {
    printf("%d -> ", i);

    ret = p[i]();
    if (ret != 0) {
      printf("\t[FAIL] returned %x\n", ret);

      errs++;
    }
  }

  return errs;
}
