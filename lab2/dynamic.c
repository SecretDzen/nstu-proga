#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dlfcn.h>

#define SIZE 256

int main(int argc, char *argv[]) {
  int outputFd, openFlags;
  mode_t filePerms;
  char str[SIZE], newStr[SIZE];

  if (argc != 3) {
    printf("To use this programm: <prog_name> <file_name> <spaces_to_delete>\n");
    exit(-1);
  }

  void *dl_hander;
  int (* readFile)(const char *fp, char *str);
  dl_hander = dlopen("lab2/libreadFile.so", RTLD_LAZY);

  if(!dl_hander) {
    printf("Wild Library Open Error appeared!\nError: %s\n", dlerror());
    exit(-1);
  }

  readFile = dlsym(dl_hander, "readFile");

  if (readFile == NULL) {
    printf("Wild Library Connection Error appeared! Error: %s\n", dlerror());
    exit(-2);
  }

  int charNums = readFile(argv[1], str);
  int spaces = 0;
  int toDelete = (int) *argv[2] - 48;

  if (toDelete < 0) {
    printf("Expected positive number of spaces\n");
    exit(-1);
  }

  for (int i = 0; i < charNums; i++) {
    if (str[i] == ' ' && spaces < toDelete) spaces++;
    else newStr[i - spaces] = str[i];
  }

  newStr[charNums - spaces] = '\0';
  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  outputFd = open("./build/lab2.text", openFlags, filePerms);
  if (outputFd == -1) {
    printf ("Error opening file %s\n ", "./build/lab2.text"); 
    exit(-3);
  }

  if(!write(outputFd, newStr, strlen(newStr))) {
    printf("Wild Error Appear!");
  }

  close (outputFd);
  printf("Program Done Sucessfully");
  return 0;
}