#include "tools.h"

int var_func(char *text, char to_delete) {
  int replace_counter = 0;
  char buffer[BUF] = {0};

  for (int i = 0; text[i]; i++) {
    char ch = text[i];

    if (ch == to_delete) {
      replace_counter++;
    } else {
      buffer[i - replace_counter] = text[i];
    }
  }

  strcpy(text, buffer);
  return replace_counter;
}
