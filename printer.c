#include "print.h"

int spacecount(int i) {
  /*
     Each character actually has two values
     in this mode; one for the content and one
     for the display option
  */
  int maxWidth = COLS * 2;

  if (i < maxWidth) {
    return maxWidth - i;
  }

  return i % maxWidth;
}

int printline(int startpos, char* dest,  char* msg, char display) {
  unsigned int idx = 0;
  unsigned int vidLocation = startpos;

  while(msg[idx] != '\0') {
    dest[vidLocation] = msg[idx];
    dest[vidLocation+1] = display;

    ++idx;
    vidLocation = vidLocation + 2;
  }

  unsigned int chars = vidLocation + spacecount(vidLocation);
  for (; vidLocation < chars; vidLocation+=2) {
    dest[vidLocation] = ' ';
    dest[vidLocation+1] = 0x05;
  }

  return vidLocation;
}
