#include "lab06.h"

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
    exit(-1);
  }

  toclient = sem_open(SEM_TOCLI, O_CREAT | O_RDONLY, 0);
  toserver = sem_open(SEM_TOSERV, O_CREAT | O_WRONLY, 0);

  for (int num = 1; num <= argc; num++) {
    char *msg = ((num == argc) ? MSG_STOP : argv[num]);
    size_t len = strlen(msg);

    check(sem_wait(toclient), -1);
    memcpy(sem_m, msg, len + 1);

    check(msync(sem_m, len, PROT_READ | PROT_WRITE), -1);
    check(sem_post(toserver), -1);
  }

  for (int num = 1; num < argc - 1; num++) {
    check(sem_post(toserver), -1);
    check(sem_wait(toclient), -1);
    printf("Recieved from server: %s\n", sem_m);
  }

  check(sem_close(toserver), -1);
  check(sem_unlink(SEM_TOSERV), -1);

  check(sem_close(toclient), -1);
  check(sem_unlink(SEM_TOCLI), -1);

  check(close(sem_d), -1);
  check(sem_unlink(SEM_NAME), -1);

  return 0;
}

void check(int x, int y) {
  if (x == y) {
    fprintf(stderr, "%s\n", strerror(errno));
    printf("Error :c");
    exit(-1);
  }
}
