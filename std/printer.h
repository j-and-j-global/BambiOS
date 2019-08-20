/**
   std/printer.h, James Condron 2019

   Provide printing functions
 **/

/**
   during boot our screen is 80 chars wide and 25 high
**/
#ifndef COLS
#define COLS 80
#endif

#ifndef LINES
#define LINES 25
#endif

/**
   spacecount takes the current length and returns the number of spaces needed to pad to fill the line
**/
int spacecount(int);

/**
   printline iterates through msg, writing each character (and the associated display value) to dest, starting at startpos.

   It returns the next starting position
**/
int printline(int startpos, char* dest, char* msg, char display);

/**
   itoa returns an int in char* form

   This implementation comes from https://wiki.osdev.org/index.php?title=Printing_To_Screen&oldid=22520, as retrieved
   20/08/2019 17:54
**/
char *itoa(int, char*, int);


/**
   ltoa_bt returns a long in char* form, with the assumption the number is in base10
**/
char *ltoa_bt(unsigned long);
