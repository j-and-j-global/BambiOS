/**
   menu.c, James Condron 2019
 **/

#include "menu.h"
#include "../std/printer.h"

char *menu_header() {
  return "BambiOS (c) 2019 - Records Subsystem";
}

char *menu_footer() {
  return "Controls: down and up move the selection down and up. 'q' will quit";
}

void nuke(char *b) {
  for (int i = 0; i < sizeof(b); i++) {
    b[i] ='\0';
  }
}

void menu_lines(int position, char* dest) {
  unsigned int i = 0;
  char header_footer_ctrl_char = 0x9F;

  i = printline(0, dest, menu_header(), header_footer_ctrl_char);

  for (int j = 0; j < 23; j++) {
    char ctrl_char = UNSELECTED_LINE_CTRL_CHAR;
    if (j == position) {
      ctrl_char = SELECTED_LINE_CTRL_CHAR;
    }

    i = printline(i, dest, record_name(j), ctrl_char);
  }

  printline(i, dest, menu_footer(), header_footer_ctrl_char);
}
