// System V IPC
// Программа из учебника "Системное программирование в среде Linux", Гунько
// А.В., стр. 86 Название: slot.c Описание: формирование объектов IPC с
// живучестью ядра
// slot.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
int main(int argc, char **argv) {
  int i, msqid;
  for (i = 0; i < 10; i++) {
    msqid = msgget(IPC_PRIVATE, IPC_CREAT);
    printf("msqid = %d\n", msqid);
    msgctl(msqid, IPC_RMID, NULL);
  }
  exit(0);
}
