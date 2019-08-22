/**
   cmos_test.c

   Stub out __asm__ calls/ code which calls __asm__ based stuff
   to return predictible values
 **/

#include "cmos.h"

unsigned char read_from_cmos(char index) {
  // 2019-08-21 16:30:01

  switch (index) {
  case 0x00:
    return 1;

  case 0x02:
    return 30;

  case 0x04:
    return 16;

  case 0x06:
    return 4;

  case 0x07:
    return 21;

  case 0x08:
    return 8;

  case 0x09:
    return 19;

  case 0x32:
    return 20;

  case 0x0B:
    return 1 | 2;
  }

  return 0;
}

int cmos_ready() {
  return 1;
}

int cmos_clock_updating() {
  return 0;
}
