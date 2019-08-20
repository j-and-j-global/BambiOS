/* Welcome strings */
char *welcomeMessage = "Welcome to BambiOS";
char *copyright = "(c) The BambiOS team, 2019";
char *booting = "booting...";
char *emptyLine = "                                                                                ";
char *pressEnter = "press enter to start";

#ifndef SLEEP_S
#define SLEEP_S 5
#endif

#ifndef SLEEP_NS
#define SLEEP_NS SLEEP_S*1000*1000
#endif

/* welcome() writes the welcome message to screen */
void welcome();

/* kmain is the kernel entrypoint */
void kmain(void);
