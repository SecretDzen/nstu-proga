#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 256

void nameGenerator(char *argument, char file[20]) {
  int i = 0;
    while (*(argument + i) != '.' && *(argument + i)) {
    file[i] = *(argument + i);
    i++;
  }
  strcat(file, ".out");
}

void convertStr(char *str, int last, int exchangeCount) {
  int i = 0;
  while (i++ < last - 1) {
    if (str[i] == str[last] && exchangeCount--) {
      str[i] = '#';
    }
    if (!exchangeCount) break;
  }
}

int main(int argc, char *argv[]) {
  int inputFd, outputFd, openFlags;
  mode_t filePerms;
  char f_out_name[20] = {0};
  char buffer, str[SIZE] = {0};
  int i, exchangeCount;

  if (argc != 3) {
    printf("Not enough arguments\n");
    return -1;
  }

  inputFd = open(argv[1], O_RDONLY);
  nameGenerator(argv[1], f_out_name);
  if (inputFd < 0) {
    printf("Error %d (%s) while open file: %s!\n", errno, strerror(errno),
           argv[1]);
    return -1;
  }

  exchangeCount = atoi(argv[2]);

  i = 0;
  while (read(inputFd, &buffer, 1) > 0) {
    str[i] = buffer;
    i++;
  }
  close(inputFd);

  int last = strlen(str) - 1;
  convertStr(str, last, exchangeCount);

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  outputFd = open(f_out_name, openFlags, filePerms);

  if (outputFd == -1) {
    printf("Error(%d): %s\nWith file: %s\n ", errno, strerror(errno), f_out_name);
    return -1;
  }

  if(write(outputFd, str, strlen(str)) <= 0) {
    printf("Write error\nError: %d - %s\n", errno, strerror(errno));
    return -1;
  }

  close(outputFd);
  printf("Done\n");
  return exchangeCount;
}
