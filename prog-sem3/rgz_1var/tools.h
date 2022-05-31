#ifndef TOOLS_H
#define TOOLS_H

#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void log_writer(int type, char* str);

#define BUF 256
#define OK 0
#define ERROR -1
#define MAX_FILES 16
#define FIFO "/tmp/_fifo"
#define LOG_FILE "log_file.log"
#define PROG_PATH "./proceed_file"
#define PROG_NAME "proceed_file"
#define O_FLAGS O_CREAT | O_WRONLY | O_TRUNC

#define try(val, err)                   \
  if (val == err) {                     \
    log_writer(ERROR, strerror(errno)); \
    exit(-1);                           \
  }

#endif  // TOOLS_H