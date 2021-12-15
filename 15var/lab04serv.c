#include "lab04.h"

int main() {
  pid_t pid = 0;
  int status = 0;
  int fd = 0, count = 0;

  char** files = calloc(MAX_FILES, sizeof(char*));

  if ((mkfifo(FIFO, 0666) == -1) && (errno != EEXIST)) {
    printf("%s\n", strerror(errno));
    return -1;
  }

  fd = open(FIFO, O_RDONLY);

  while (true) {
    int len = 0;
    char* buf = NULL;

    read(fd, &len, sizeof(int));
    buf = calloc(len, sizeof(char));

    read(fd, buf, len + 1);

    if (strlen(buf) == 0) {
      free(buf);
      break;
    }

    printf("From client %s\n", buf);
    files[count++] = buf;
  }
  close(fd);

  fd = open(FIFO, O_WRONLY);

  for (int num = 0; num < count - 1; num++) {
    pid = fork();

    if (pid == 0) {
      execl(LAB2_PATH, LAB2_NAME, files[num], files[count - 1], NULL);
    } else if (pid > 0) {
      int child = wait(&status);

      if (child > 0) {
        char* result_status = calloc(RES_LEN, sizeof(char*));
        sprintf(result_status, "File %s done with %s changes", files[num],
                files[count - 1]);
        int len = strlen(result_status);

        if ((write(fd, &len, sizeof(len)) == -1) ||
            (write(fd, result_status, len + 1) == -1)) {
          return -1;
        }

        free(result_status);
      }
    }
  }
  close(fd);

  for (int num = 0; num < MAX_FILES; num++) free(files[num]);
  free(files);

  return 0;
}
