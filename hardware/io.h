/**
   io.h, James Condron 2019

   Provide access to devices and other assorted io ports
 **/

/**
   inb_p reads a byte from an io port
 **/
unsigned char inb_p(unsigned short int);

/**
   outb_p writes a byte to an io port
 **/
void outb_p(unsigned char, unsigned short int);
