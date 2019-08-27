#ifndef SLEEP_S
#define SLEEP_S 5
#endif

/**
   welcome writes the welcome message to screen *
 **/
unsigned int welcome(char*);

/**
   initialiser initialises anything that needs initialising
 **/
unsigned int initialiser(int, char*);

/**
   startup will boot into the main kernel routine
 **/
unsigned int startup(int, char*);

/**
   cls will clear the screen
**/
void cls(char*);

/**
   kmain is the kernel entrypoint
**/
void kmain(void);

/**
   byebye is a call defined in asm which will shutdown the kernel and, thus,
   the machine
**/
extern void byebye(void);
