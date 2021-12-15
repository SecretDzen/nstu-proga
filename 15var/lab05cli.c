#include "lab05.h"

int main(int argc, char *argv[]) {
  mqd_t mq;
  struct mq_attr attr;

  /* initialize the queue attributes */
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = MAX_SIZE;
  attr.mq_curmsgs = 0;

  /* open the mail queue */
  mq = mq_open(QUEUE_TOSERVER, O_CREAT | O_WRONLY);
  check(mq, -1);

  for (int num = 1; num <= argc; num++) {
    char *msg = ((num == argc) ? MSG_STOP : argv[num]);
    int mqs = mq_send(mq, msg, strlen(msg) + 1, 0);
    check(mqs, -1);
  }

  /* cleanup */
  mqd_t close = mq_close(mq);
  check(close, -1);

  /* get server results */
  mq = mq_open(QUEUE_TOCLIENT, O_CREAT | O_RDONLY, 0666, &attr);

  for (int num = 1; num < argc - 1; num++) {
    char *buf = calloc(attr.mq_msgsize, sizeof(char));

    int mqr = mq_receive(mq, buf, attr.mq_msgsize, 0);
    check(mqr, -1);

    printf("Recieved from server: %s\n", buf);
    free(buf);
  }

  close = mq_close(mq);
  check(close, -1);

  return 0;
}

void check(int x, int y) {
  if (x == y) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(-1);
  }
}
