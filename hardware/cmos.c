/**
cmos.c

Most of this code is a reimagining (in places in fact a direct copy)
of sample code at https://wiki.osdev.org/CMOS

**/

#include "cmos.h"


/**
   The following two functions (outb_p, inb_p) come from /usr/include/sys/io.h on my build machine:

   Linux seoul-flower 5.2.9-arch1-1-ARCH #1 SMP PREEMPT Fri Aug 16 11:29:43 UTC 2019 x86_64 GNU/Linux
**/

unsigned char inb_p (unsigned short int __port) {
  unsigned char _v;

  __asm__ __volatile__ ("inb %w1,%0\noutb %%al,$0x80":"=a" (_v):"Nd" (__port));
  return _v;
}

void outb_p (unsigned char __value, unsigned short int __port) {
  __asm__ __volatile__ ("outb %b0,%w1\noutb %%al,$0x80": :"a" (__value),
                        "Nd" (__port));
}

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
