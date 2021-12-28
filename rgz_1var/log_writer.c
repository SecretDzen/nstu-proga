#include "tools.h"

void log_writer(int type, char* str) {
    char msg[BUF] = {0};
    int fd = 0;

    if (type == ERROR) {
        snprintf(msg, BUF -1, "=== ERROR ===\nDESCR: %s\n", str);
    } else if (type == OK) {
        snprintf(msg, BUF - 1, ">> OK: %s\n", str);
    }

    try((fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0666)), -1);
    try(write(fd, msg, strlen(msg)), -1);
    try(close(fd), -1);
}
