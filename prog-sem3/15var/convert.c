#include "convert.h"

void nameGenerator(char *argument, char file[20]) {
  int i = 0;
    while (*(argument + i) != '.' && *(argument + i)) {
    file[i] = *(argument + i);
    i++;
  }
  strcat(file, ".out");
}

void convert(char *str, int last, int exchangeCount) {
  int i = 0;
  while (i++ < last - 1) {
    if (str[i] == str[last] && exchangeCount--) {
      str[i] = '#';
    }
    if (!exchangeCount) break;
  }
}