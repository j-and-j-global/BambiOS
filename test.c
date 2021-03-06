#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "std/printer.h"
#include "std/time.h"
#include "std/strings.h"
#include "driver/rtc.h"
#include "app/app_gen.h"

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
  printf("test_cpy()\n");

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

int test_record_track_offset() {
  printf("record_track_offset()\n");

  char buffer[80];
  char *expect = ", ONE 2 - Who Is Who, ONE 3 - Wrecking Crew, ONE 4 - L.A. Girl, ONE 5 - Self Des";

  record_track_offset(0, 23, buffer);

  if (strcmp(buffer, expect) != 0) {
    printf("\trecord_track_offset(): expected '%s', received '%s'\n", expect, buffer);

    return 1;
  }

  return 0;
}

int test__len() {
  printf("test__len()\n");

  char *s = "Hello, World!";
  int len = _len(s);

  if (len != 13) {
    printf("\t_len(): expected %d, received %d\n", 13, len);

    return 1;
  }

  return 0;
}

int test__len2() {
  printf("test__len2()\n");

  char *s = tracks[0];
  int len = _len(s);

  if (len != 270) {
    printf("\t_len(): expected %d, received %d\n", 270, len);

    return 1;
  }

  return 0;
}

int test_record_track_offset2() {
  printf("test_record_track_offset2()\n");

  // This should return from 190, since there are 270 chars and we want to always
  // show 80 if there are that many (at least) available.

  char buf[81];
  record_track_offset(0, 250, buf);

  int l = strlen(buf);
  if (l != 80) {
    printf("\tstrlen(): expected %d, received %d\n", 80, l);

    return 1;
  }

  char *expectStr = "ack, TWO 4 - Rip It Up, TWO 5 - Democracy, TWO 6 - No Friends, TWO 7 - Creatures";
  if (strcmp(expectStr, buf) != 0) {
    printf("\trecord_track_offset(): expected '%s', received '%s'\n", expectStr, buf);

    for (int i = 0 ; i < 80; i++) {
      printf("%d: %c -> %X\n", i+1, buf[i], buf[i]);
    }

    return 1;
  }

  return 0;
}

int null() {
  return 0;
}

int main(void) {
  const int tests = 12;

  int (*p[12]) () = {
    test_rtc, test_unixtime, test_spacecount, test_spacecount2, test_ltoa_bt, test_itoa, test_iso8601_ish, test_cpy, test_record_track_offset, test_record_track_offset2, test__len, test__len2,
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

  if (errs == 0) {
    printf("\n\nSuccess!\n");
  }

  return errs;
}
