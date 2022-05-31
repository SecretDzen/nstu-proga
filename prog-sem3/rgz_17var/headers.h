#ifndef HEADERS_H
#define HEADERS_H

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include "log.h"

#define MEM1 "/dev/shm/test1"
#define MEM2 "/dev/shm/test2"
#define NAME1 "test1"
#define NAME2 "test2"
#define SIZE 128
#define MAX_NAME 256
#define PROT (PROT_READ | PROT_WRITE)
#define FLAGS (O_RDWR | O_CREAT)
#define MODE 0666
#define EBUF_SIZE (3 * sizeof(struct inotify_event) + 1)
#define PATH "./prog"
#define BIN_NAME "prog"

// #define DEBUG

void waitMem(const char* mem_name);

void readFromClient(int ifd, void* buf, size_t len);
void sendToClient(const void* buf, size_t len);

void sendToServer(const void* buf, size_t len);
void readFromServer(int ifd, void* buf, size_t len);

#endif
