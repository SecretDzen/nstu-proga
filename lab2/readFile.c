#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int readFile(const char *fp, char *str) {
  int inputFd, charNums = 0;
  char buf;
  inputFd = open(fp, O_RDONLY);

  if (inputFd < 0) {
    printf("Error %d (%s) while open file: %s!\n",errno, strerror(errno), fp);
    exit(-2);
  }

  while (read(inputFd, &buf, 1) > 0) {
    str[charNums] = buf;
    charNums++;
  }

  close(inputFd);
  return charNums;
}