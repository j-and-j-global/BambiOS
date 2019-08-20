#include <stdio.h>
#include <stdlib.h>

#include "std/printer.h"
#include "driver/rtc.h"

int testUnixtime() {
  unixtime();
  //  printf("unixtime(): %llu\n", unixtime());

  return 0;
}

int main(void) {
  int i;

  i = testUnixtime();
  if (i != 0) {
    return i;
  }


  return 0;
}
