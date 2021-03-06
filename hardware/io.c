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
