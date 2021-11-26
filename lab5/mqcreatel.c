// Очереди сообщений Posix в Linux
// Программа из учебника "Системное программирование в среде Linux", Гунько
// А.В., стр. 110 Название: mqcreate.c Описание: создание очереди сообщений
// pxmsg/mqcreate1.c
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILE_MODE S_IRUSR | S_IWUSR
int main(int argc, char **argv) {
  int c, flags;
  mqd_t mqd;
  flags = O_RDWR | O_CREAT;
  while ((c = getopt(argc, argv, "e")) != -1) {
    switch (c) {
      case 'e':
        flags |= O_EXCL;
        break;
    }
  }
  if (optind != argc - 1) {
    printf("usage: mqcreate [ -e ] <name>\n");
    exit(-1);
  }
  // printf("%s\n", argv[optind]);
  mqd = mq_open(argv[optind], flags, FILE_MODE, NULL);
  // printf("Created %ld\n",(long)mqd);
  printf("Result:%s\n", strerror(errno));
  mq_close(mqd);
  exit(0);
}
