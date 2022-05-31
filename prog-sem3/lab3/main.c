#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  int status = 0;

  for (int k = 1; k < argc - 1; k++) {
    pid = fork();

    if (pid == 0) {
      if (execl("./build/lab_2d", "lab_2d", argv[k], argv[argc - 1], NULL) < 0) {
        printf("ERROR: %s %s\n",argv[k], argv[argc - 1]);
        exit(-1);
      } else {
        printf("Processing of file %s started (pid=%d)\n", argv[k], pid);
      }
    }
    printf("FILES: ARGV[%d] = %s\n", k, argv[k]);
  }

  if (pid > 0) {
    while (wait(&status) > 0) {}
    if (errno != ECHILD) {
      printf("Error: %s\n", strerror(errno));
    }
  }

  return 0;
}