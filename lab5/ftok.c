// System V IPC
// Программа из учебника "Системное программирование в среде Linux", Гунько
// А.В., стр. 81 Название: ftok.c Описание: формирование ключа IPC
// ftok.c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
  struct stat Stat;
  int proj_id = 210;

  if (argc != 2) {
    printf("usage: ftok <pathname>");
    exit(-1);
  }

  stat(argv[1], &Stat);
  key_t ftok_key = ftok(argv[1], proj_id);

  if (ftok_key == -1) {
    printf("ftok: %s", strerror(errno));
  } else if (ftok_key == 1) {
    printf("Error with getting ftok key\nftok: %s", strerror(errno));
  } else {
    printf("st_dev: %lx, st_ino: %lx, key: %x", (u_long)Stat.st_dev,
           (u_long)Stat.st_ino, ftok_key);
  }

  exit(0);
}
