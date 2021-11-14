#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "readFile.h"

#define SIZE 256

int main(int argc, char *argv[]) {
  int outputFd, openFlags;
  mode_t filePerms;
  char str[SIZE] = {0}, newStr[SIZE] = {0};

  if (argc != 3) {
    printf("To use this programm: <prog_name> <file_name> <spaces_to_delete>\n");
    exit(-1);
  }

  int charNums = readFile(argv[1], str);
  int spaces = 0;
  int toDelete = atoi(argv[2]);

  if (toDelete < 0) {
    printf("Expected positive number of spaces\n");
    exit(-1);
  }

  for (int i = 0; i < charNums; i++) {
    if (str[i] == ' ' && spaces < toDelete) spaces++;
    else newStr[i - spaces] = str[i];
  }

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  outputFd = open("./build/lab2s.text", openFlags, filePerms);
  if (outputFd == -1) {
    printf ("Error opening file %s\n ", "./build/lab2s.text"); 
    exit(-1);
  }

  if(write(outputFd, newStr, strlen(newStr)) <= 0) {
    printf("Wild Error Appear!\nError: %d - %s\n", errno, strerror(errno));
    close(outputFd);
    exit(-1);
  }

  close (outputFd);
  printf("Program Done Sucessfully");
  return 0;
}
