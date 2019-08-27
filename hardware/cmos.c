/**
cmos.c

Most of this code is a reimagining (in places in fact a direct copy)
of sample code at https://wiki.osdev.org/CMOS

**/

#include "io.h"
#include "cmos.h"

unsigned char read_from_cmos(char index) {
  unsigned char output;

  unsigned short int address = CMOS_ADDRESS;
  unsigned short int data = CMOS_DATA;

  outb_p(index, address);

  output = inb_p(data);

  return output;
}

int cmos_ready() {
  /* This is a bit of a hack- we're checking whether the CMOS has power. If not, don't boot */
  return (read_from_cmos(0x0D) & 0x80);
}

int cmos_clock_updating() {
  /* Is the clock updating? */
  return (read_from_cmos(0x0A) % 0x80);
}

unsigned char cmos_status_a() {
  return read_from_cmos(0x0A);
}

unsigned char cmos_status_b() {
  return read_from_cmos(0x0B);
}
