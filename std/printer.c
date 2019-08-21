#include "printer.h"

int spacecount(int i) {
  /*
     Each character actually has two values
     in this mode; one for the content and one
     for the display option
  */
  int chars = i/2;

  if (chars < COLS) {
    return COLS - chars;
  }

  return COLS - (chars % COLS);
}

int printline(int startpos, char* dest,  char* msg, char display) {
  unsigned int idx = 0;
  unsigned int vidLocation = startpos;

  while(msg[idx] != '\0') {
    dest[vidLocation] = msg[idx];
    dest[vidLocation+1] = display;

    ++idx;
    vidLocation += 2;
  }

  int spaces = spacecount(vidLocation);
  for (int i = 0; i < spaces; i++) {
    dest[vidLocation] = ' ';
    dest[vidLocation+1] = 0x05;

    vidLocation += 2;
  }

  return vidLocation;
}

/**
   This is pretty much our itoa, but with a long and without
   the base stuff- we're always base10
**/
char *ltoa_bt(unsigned long value) {
  char *rc;
  char *ptr;
  char *low;

  rc = ptr = "";
  low = ptr;

  do {
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % 10];

      value /= 10;
    } while ( value );

  *ptr-- = '\0';

  while ( low < ptr ) {
      char tmp = *low;
      *low++ = *ptr;
      *ptr-- = tmp;
    }

  return rc;
}

/* From: https://wiki.osdev.org/Printing_To_Screen */
char *itoa(int value, char *str, int base) {
    char *rc;
    char *ptr;
    char *low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}
