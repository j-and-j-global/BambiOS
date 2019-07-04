/* during boot our screen is 80 chars wide and 25 high */
#ifndef COLS
#define COLS 80
#endif

#ifndef LINES
#define LINES 25
#endif

/* spacecount takes the current length and returns the number of spaces needed to pad to fill the line */
int spacecount(int);

/* printline iterates through msg, writing each character (and the associated display value) to dest, starting at startpos. It returns the next starting position*/
int printline(int startpos, char* dest, char* msg, char display);
