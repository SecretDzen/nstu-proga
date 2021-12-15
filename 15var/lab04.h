#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LAB2_PATH "./lab02d"
#define LAB2_NAME "lab02d"
#define FIFO "/tmp/_fifo"
#define RES_LEN 64
#define MAX_FILES 16
