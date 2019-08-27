/**
   menu.h, James Condron 2019

   Produce a simple menu system for showing *stuff*
 **/

/**
   menu_header returns the top line of the menu
 **/
char *menu_header();

/**
   menu_footer returns the bottom line of the menu
 **/
char *menu_footer();

/**
   menu_full returns the full menu as an array of lines
 **/
void menu_lines(int position, int topline, char* dest);

/**
   menu control chars
**/

#ifndef UNSELECTED_LINE_CTRL_CHAR
#define UNSELECTED_LINE_CTRL_CHAR 0x07
#endif

#ifndef SELECTED_LINE_CTRL_CHAR
#define SELECTED_LINE_CTRL_CHAR 0x70
#endif
