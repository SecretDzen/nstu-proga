#include "lab05.h"

int main() {
  mqd_t mq;
  struct mq_attr attr;
  int must_stop = 0;
  int count = 0;

  /* initialize the queue attributes */
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = MAX_SIZE;
  attr.mq_curmsgs = 0;

  char **files = calloc(MAX_FILES, sizeof(char *));

  /* create the message queue */
  mq = mq_open(QUEUE_TOSERVER, O_CREAT | O_RDONLY, 0666, &attr);
  check(mq, -1);

  do {
    ssize_t bytes_read;
    char *buffer = calloc(attr.mq_msgsize, sizeof(char *));

    /* receive the message */
    bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
    if (bytes_read <= 0) {
      printf("Read error");
      exit(-1);
    }

    buffer[bytes_read] = '\0';

    if (!strcmp(buffer, MSG_STOP)) {
      must_stop = 1;
      free(buffer);
    } else {
      printf("Received from client: %s\n", buffer);
      files[count++] = buffer;
    }
  } while (!must_stop);

  /* cleanup */
  mqd_t close = mq_close(mq);
  check(close, -1);

  /* create the message queue */
  mq = mq_open(QUEUE_TOCLIENT, O_CREAT | O_WRONLY, 0666, &attr);
  check(mq, -1);

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
        int mqs = mq_send(mq, result_status, strlen(result_status), 0);
        check(mqs, -1);
      }
    }
  }

  /* cleanup */
  mqd_t close2 = mq_close(mq);
  check(close2, -1);

  mqd_t unlink = mq_unlink(QUEUE_TOSERVER);
  check(unlink, -1);

  /* free buffer */
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
