#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define LAB2_PATH "./build/lab_2d"
#define LAB2_NAME "lab_2d"
#define SEM_NAME "/mysem"
#define SEM_TOCLI "/tocli"
#define SEM_TOSERV "/toserv"
#define MSG_STOP "exit"
#define MAX_FILES 10
#define SHM_SIZE 64

void check(int x, int y);

int main(int argc, char *argv[]) {
  int sem_d = 0;

  sem_t *toclient = NULL;
  sem_t *toserver = NULL;
  char *sem_m = NULL;

  sem_d = shm_open(SEM_NAME, O_RDWR | O_CREAT, 0666);
  ftruncate(sem_d, SHM_SIZE);
  check(sem_d, -1);

  sem_m = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, sem_d, 0);
  check(close(sem_d), -1);

  if (sem_m == MAP_FAILED) {
    printf("SEM_M: %s", strerror(errno));
    exit(-1);
  }

  toclient = sem_open(SEM_TOCLI, O_CREAT | O_RDWR, 0);
  toserver = sem_open(SEM_TOSERV, O_CREAT | O_RDWR, 0);

  for (int num = 1; num <= argc; num++) {
    char *msg = ((num == argc) ? MSG_STOP : argv[num]);
    size_t len = strlen(msg);
    printf("MSG: %s\n", msg);

    check(sem_wait(toclient), -1);
    memcpy(sem_m, msg, len + 1);
    printf("SEM_M: %s\n", sem_m);

    check(msync(sem_m, len, PROT_READ | PROT_WRITE), -1);
    check(sem_post(toserver), -1);
  }

  for (int num = 1; num < argc - 1; num++) {
    check(sem_post(toserver), -1);
    check(sem_wait(toclient), -1);
    printf("Recieved from server: %s\n", sem_m);
  }

  check(sem_close(toserver), -1);
  check(sem_close(toclient), -1);
  check(munmap(sem_m, SHM_SIZE), -1);

  return 0;
}

void check(int x, int y) {
  if (x == y) {
    fprintf(stderr, "%s\n", strerror(errno));
    printf("Error :c");
    exit(-1);
  }
}
