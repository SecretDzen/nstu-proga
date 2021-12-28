#include "tools.h"

void server_start();

int main() {
  int pid = 0;
  try((pid = fork()), ERROR);

  if (pid == 0) {
    umask(0);
    try(setsid(), -1);
    try(close(STDIN_FILENO), -1);
    try(close(STDOUT_FILENO), -1);
    try(close(STDERR_FILENO), -1);

    server_start();
  }

  return 0;
}

void server_start() {
  log_writer(OK, "SERVER STARTED\n");
  pid_t pid = 0;
  int status = 0;
  int fd = 0, count = 0;

  char** files = calloc(MAX_FILES, sizeof(char*));

  if ((mkfifo(FIFO, 0666) == ERROR) && (errno != EEXIST)) {
    log_writer(ERROR, strerror(errno));
    exit(-1);
  }

  fd = open(FIFO, O_RDONLY);
  try(fd, ERROR);

  while (1) {
    int len = 0;
    char* buf = NULL;
    char msg[BUF] = {0};

    read(fd, &len, sizeof(int));
    buf = calloc(len, sizeof(char));

    read(fd, buf, len + 1);

    if (strlen(buf) == 0) {
      free(buf);
      break;
    }

    snprintf(msg, BUF - 1, "Recieved from client %s", buf);
    log_writer(OK, msg);
    files[count++] = buf;

    if (count == MAX_FILES) break;
  }

  close(fd);
  fd = open(FIFO, O_WRONLY);
  try(fd, ERROR);

  for (int num = 0; num < count - 1; num++) {
    pid = fork();

    if (pid == 0) {
      char process_status[BUF] = {0};
      snprintf(process_status, BUF - 1, "Proceeding file: %s", files[num]);
      log_writer(OK, process_status);
      try(execl(PROG_PATH, PROG_NAME, files[num], files[count - 1], NULL),
          ERROR);
    } else if (pid > 0) {
      int child = wait(&status);

      if (child > 0) {
        char* result_status = calloc(BUF, sizeof(char*));
        int log_status = 0;

        if (WEXITSTATUS(status) == 255) {
          snprintf(result_status, BUF - 1, "%s: error\n", files[num]);
          log_status = -1;
        } else {
          snprintf(result_status, BUF - 1, "File %s proceeded. Replaced: %d\n",
                   files[num], WEXITSTATUS(status));
        }

        int len = strlen(result_status);
        log_writer(log_status, result_status);

        try(write(fd, &len, sizeof(len)), ERROR);
        try(write(fd, result_status, len + 1), ERROR);

        free(result_status);
      }
    }
  }
  close(fd);

  for (int num = 0; num < MAX_FILES; num++) free(files[num]);
  free(files);

  return 0;
}
