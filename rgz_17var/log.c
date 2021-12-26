#include "log.h"

void writeLog(int type, char* str) {
    char m[120] = {0};
    int fd = 0;

    if (type == ERROR) {
        snprintf(m, 119, "!! %s !!: %s\n", ERROR_PREFIX, str);
    } else if (type == INFO) {
        snprintf(m, 119, ">> %s: %s\n", INFO_PREFIX, str);
    }

    try((fd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0666)), -1);
    try(write(fd, m, strlen(m) + 1), -1);
    try(close(fd), -1);
}
