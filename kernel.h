/* Welcome strings */
char *welcomeMessage = "Welcome to BambiOS";
char *copyright = "(c) The BambiOS team, 2019";
char *booting = "booting...";
char *emptyLine = " ";
char *pressEnter = "press enter to start";

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

/* kmain is the kernel entrypoint */
void kmain(void);
