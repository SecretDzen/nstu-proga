#include "lab04.h"

int main(int argc, char **argv) {
  int fd = 0;

  if ((mkfifo(FIFO, 0666) == -1) && (errno != EEXIST)) {
    printf("%s\n", strerror(errno));
    return -1;
  }

  fd = open(FIFO, O_WRONLY);

  for (int num = 1; num < argc; num++) {
    int len = strlen(argv[num]);

    if ((write(fd, &len, sizeof(len)) < 0) ||
        (write(fd, argv[num], len + 1) < 0)) {
      return -1;
    }
  }

  close(fd);
  fd = open(FIFO, O_RDONLY);

  while (true) {
    int len = 0;
    char *buf = calloc(RES_LEN, sizeof(char));

    read(fd, &len, sizeof(len));
    read(fd, buf, len + 1);

    if (strlen(buf) == 0) {
      free(buf);
      break;
    }

    printf("From server: %s\n", buf);

    free(buf);
  }

  close(fd);

  return 0;
}
