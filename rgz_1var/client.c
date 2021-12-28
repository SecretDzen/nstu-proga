#include "tools.h"

int main(int argc, char **argv) {
  int fd = 0;

  if (argc < 3) {
    printf("Usage: ./client <files.txt, [...]> <char_to_replace>'\n");
    exit(-1);
  }

  if ((mkfifo(FIFO, 0666) == -1) && (errno != EEXIST)) {
    log_writer(ERROR, strerror(errno));
    exit(-1);
  }

  fd = open(FIFO, O_WRONLY);
  try(fd, ERROR);

  for (int num = 1; num < argc; num++) {
    int len = strlen(argv[num]);

    if ((write(fd, &len, sizeof(len)) < 0) ||
        (write(fd, argv[num], len + 1) < 0)) {
      log_writer(ERROR, strerror(errno));
      exit(-1);
    }
  }

  try(close(fd), ERROR);
  fd = open(FIFO, O_RDONLY);
  try(fd, ERROR);

  while (1) {
    int len = 0;
    char *buf = calloc(BUF, sizeof(char));

    try(read(fd, &len, sizeof(len)), ERROR);
    try(read(fd, buf, len + 1), ERROR);

    if (strlen(buf) == 0) {
      free(buf);
      break;
    }

    printf("From server: %s", buf);
    free(buf);
  }

  try(close(fd), ERROR);
  return 0;
}
