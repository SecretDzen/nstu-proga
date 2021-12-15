#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define LAB2_PATH "./lab02d"
#define LAB2_NAME "lab02d"
#define SEM_NAME "/mysem"
#define SEM_TOCLI "/tocli"
#define SEM_TOSERV "/toserv"
#define MSG_STOP "exit"
#define MAX_FILES 10
#define SHM_SIZE 64

void check(int x, int y);