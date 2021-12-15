#include "lab06.h"

int main() {
  int sem_d = 0;
  int must_stop = 0;
  int count = 0;

  char **files = calloc(MAX_FILES, sizeof(char *));

  char *shm = NULL;
  sem_t *toclient = NULL;
  sem_t *toserver = NULL;

  sem_d = shm_open(SEM_NAME, O_RDWR | O_CREAT, 0666);
  check(sem_d, -1);

  shm = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, sem_d, 0);
  if (shm == MAP_FAILED) {
    printf("%s", strerror(errno));
    exit(-1);
  }

  toclient = sem_open(SEM_TOCLI, O_RDONLY | O_CREAT, 0666, 0);
  toserver = sem_open(SEM_TOSERV, O_WRONLY | O_CREAT, 0666, 0);

  do {
    sem_post(toclient);
    sem_wait(toserver);
    size_t len = strlen(shm);
    char *buffer = calloc(len, sizeof(char *));

    if (len <= 0) {
      printf("Read error");
      exit(-1);
    }

    buffer = strncpy(buffer, shm, len);
    if (!strcmp(buffer, MSG_STOP)) {
      must_stop = 1;
      free(buffer);

    } else {
      printf("Received from client: %s\n", buffer);
      files[count++] = buffer;
    }
  } while (!must_stop);

  pid_t pid = 0;
  int status = 0;

  for (int num = 0; num < count - 1; num++) {
    pid = fork();

    if (pid == 0) {
      execl(LAB2_PATH, LAB2_NAME, files[num], files[count - 1], NULL);

    } else if (pid > 0) {
      int child = wait(&status);

      if (child > 0) {
        char result_status[128];
        sprintf(result_status, "File %s done with %s changes", files[num],
                files[count - 1]);

        check(sem_wait(toserver), -1);

        size_t len = strlen(result_status);

        memcpy(shm, result_status, len);
        check(msync(shm, len, PROT_READ | PROT_WRITE), -1);
        check(sem_post(toclient), -1);
      }
    }
  }

  check(sem_close(toserver), -1);
  check(sem_unlink(SEM_TOSERV), -1);

  check(sem_close(toclient), -1);
  check(sem_unlink(SEM_TOCLI), -1);

  
  check(close(sem_d), -1);
  check(sem_unlink(SEM_NAME), -1);

  for (int num = 0; num < MAX_FILES; num++) free(files[num]);
  free(files);

  return 0;
}

void check(int x, int y) {
  if (x == y) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(-1);
  }
}
