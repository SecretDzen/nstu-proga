#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dlfcn.h>

#define SIZE 256

int main(int argc, char *argv[]) {
  int inputFd, outputFd, openFlags;
  mode_t filePerms;
  char f_out_name[20] = {0};
  char buffer, str[SIZE] = {0};
  int i;

  if (argc != 3) {
    printf("Not enough arguments\n");
    return -1;
  }

  void *dl_hander;
  dl_hander = dlopen("libconvert.so", RTLD_LAZY);

  if(!dl_hander) {
    printf("Library Open Error\n%s\n", dlerror());
    return -1;
  }

  void (* nameGenerator)(char *argument, char file[20]);
  nameGenerator = dlsym(dl_hander, "nameGenerator");
  nameGenerator(argv[1], f_out_name);

  inputFd = open(argv[1], O_RDONLY);
  if (inputFd < 0) {
    printf("Error %d (%s) while open file: %s!\n", errno, strerror(errno),
           argv[1]);
    return -1;
  }

  i = 0;
  while (read(inputFd, &buffer, 1) > 0) {
    str[i] = buffer;
    i++;
  }
  close(inputFd);

  int (* convert)(char *str, int last, int exchangeCount);
  convert = dlsym(dl_hander, "convert");

  if (convert == NULL) {
    printf("Wild Library Connection Error appeared! Error: %s\n", dlerror());
    exit(-1);
  }

  int exchangeCount = atoi(argv[2]);
  int last = strlen(str) - 1;
  convert(str, last, exchangeCount);

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
  return 0;
}
