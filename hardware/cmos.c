/**
cmos.c

Most of this code is a reimagining (in places in fact a direct copy)
of sample code at https://wiki.osdev.org/CMOS

**/

#include "cmos.h"


/**
   The following two functions (outb_p, inb_p) come from /usr/include/sys/io.h on my build machine:

   Linux seoul-flower 5.2.5-arch1-1-ARCH #1 SMP PREEMPT Wed Jul 31 08:30:34 UTC 2019 x86_64 GNU/Linux
**/
static __inline void
outb_p (unsigned char __value, unsigned short int __port)
{
  __asm__ __volatile__ ("outb %b0,%w1\noutb %%al,$0x80": :"a" (__value),
                        "Nd" (__port));
}

static __inline unsigned char
inb_p (unsigned short int __port)
{
  unsigned char _v;

  __asm__ __volatile__ ("inb %w1,%0\noutb %%al,$0x80":"=a" (_v):"Nd" (__port));
  return _v;
}

unsigned char read_from_cmos(char index) {
  unsigned char output;

  char address = CMOS_ADDRESS;
  char data = CMOS_DATA;

  outb_p(address, index);

  output = inb_p(data);

  return output;
}

int cmos_ready() {
  return (read_from_cmos(0x10) & 0x80);
}
