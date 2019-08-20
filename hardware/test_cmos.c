/**
   cmos_test.c

   Stub out __asm__ calls/ code which calls __asm__ based stuff
   to return predictible values
 **/

#include "cmos.h"

unsigned char read_from_cmos(char index) {
  return index;
}
