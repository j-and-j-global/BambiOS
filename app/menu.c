/**
   menu.c, James Condron 2019
 **/

#include "menu.h"
#include "app_gen.h"
#include "../vid.h"
#include "../kernel.h"
#include "../driver/keyboard.h"
#include "../hardware/io.h"
#include "../std/printer.h"
#include "../std/strings.h"

int page_start = 0;
int line_start = 0;
int highlighted = 0;
char *footer = "Controls: arrow keys to move the selection. 'q' will quit";

char *menu_header() {
  return "BambiOS (c) 2019 - Records Subsystem";
}

char *menu_footer() {
  return footer;
}

void nuke(char *b) {
  for (int i = 0; i < sizeof(b); i++) {
    b[i] ='\0';
  }
}

void menu_lines(int position, int topline, char* dest) {
  unsigned int i = 0;
  char header_footer_ctrl_char = 0x9F;

  i = printline(0, dest, menu_header(), header_footer_ctrl_char);

  for (int j = topline; j < (topline + 23); j++) {
    char ctrl_char = UNSELECTED_LINE_CTRL_CHAR;
    if (j == position) {
      ctrl_char = SELECTED_LINE_CTRL_CHAR;
    }

    i = printline(i, dest, record_name(j), ctrl_char);
  }

  printline(i, dest, menu_footer(), header_footer_ctrl_char);
}

void scroll_menu(void) {
  unsigned char status;
  char keycode;

  /* write EOI */
  outb_p(0x20, 0x20);

  status = inb_p(KEYBOARD_STATUS_PORT);
  /* Lowest bit of status will be set if buffer is not empty */
  if (status & 0x01) {
    keycode = inb_p(KEYBOARD_DATA_PORT);
    if(keycode < 0)
      return;
  }

  switch (keycode) {
  case 16:
    byebye();

    break;

  case 71:
    highlighted -= 23;
    line_start = 0;

    break;

  case 72: case 17:
    highlighted--;
    line_start = 0;

    break;

  case 75: case 30:
    line_start--;

    break;

  case 77: case 32:
    line_start++;

    break;

  case 80: case 31:
    highlighted++;
    line_start = 0;

    break;

  case 81:
    highlighted += 23;
    line_start = 0;

    break;
  }

  if (line_start < 0) {
    line_start = 0;
  }

  if (highlighted < 0) {
    highlighted = 0;
  } else if (highlighted > RECORDS_COUNT) {
    highlighted = RECORDS_COUNT;
  }

  if (line_start > (_len(tracks[highlighted]) - 80)) {
    line_start = _len(tracks[highlighted]) - 80;
  }

  char ib[81];
  footer = record_track_offset(highlighted, line_start, ib);

  page_start = framestart(page_start, highlighted);
  menu_lines(highlighted, page_start, vidptr);
}

int framestart(int old_start, int cursor) {
  if (cursor < 0) {
    return 0;
  }

  if (cursor > (old_start + 22)) {
    return old_start + 1;
  }

  if (cursor < old_start) {
    return old_start - 1;
  }

  return old_start;
}
