#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LAB2_PATH "./lab02d"
#define LAB2_NAME "lab02d"
#define QUEUE_TOSERVER "/to_server"
#define QUEUE_TOCLIENT "/to_client"
#define MAX_SIZE 1024
#define RES_LEN 64
#define MSG_STOP "exit"
#define MAX_FILES 10

void check(int x, int y);
