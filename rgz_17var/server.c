#include "headers.h"

void myserver();

int main()
{
    int pid = 0;
    try((pid = fork()), -1);

    if (pid == 0) {
        writeLog(INFO, "server started");
        umask(0);
        try(setsid(), -1);
        try(close(STDIN_FILENO), -1);
        try(close(STDOUT_FILENO), -1);
        try(close(STDERR_FILENO), -1);

        myserver();
    }
    
    return 0;
}

void myserver()
{
    int ifd = 0;
    int status = 0;
    int child = 0;
    pid_t pid = 0;
    size_t count = 0;
    size_t files_num = 0;
    char** files;

    try((ifd = inotify_init()), -1);

    readFromClient(ifd, &files_num, sizeof(files_num));
    files = calloc(files_num, sizeof(char*));

    sleep(1);
    readFromClient(ifd, &count, sizeof(count));

    for (size_t n = 0; n < files_num; n++) {
        char* msg = calloc(MAX_NAME, sizeof(char));
        char m[80] = {0};
        writeLog(INFO, "listening...");

        sleep(1);
        readFromClient(ifd, msg, MAX_NAME);
        snprintf(m, 79, "message from client: %s", msg);
        writeLog(INFO, m);

        files[n] = msg;
    }

    for (size_t n = 0; n < files_num; n++) {
        try((pid = fork()), -1);

        if (pid == 0) {
            char count_arg[10] = {0};
            char m[80] = {0};

            snprintf(count_arg, 9, "%lu", count);
            snprintf(m, 79, "processing %s...", files[n]);

            writeLog(INFO, m);
            try(execl(PATH, BIN_NAME, files[n], count_arg, NULL), -1);
        } else {
            try((child = wait(&status)), -1);

            if (child > 0) {
                int r = WEXITSTATUS(status);
                char m[80] = {0};
                
                sendToClient(&r, sizeof(r));
                snprintf(m, 79, "message `%d` sended to client", r);
                writeLog(INFO, m);
            }
        }
    }
    
    for (size_t n = 0; n < files_num; n++) {
        free(files[n]);
    }
    free(files);
}

void readFromClient(int ifd, void* buf, size_t len)
{
    int fd, wd;
    char ebuf[EBUF_SIZE] = {0};
    void* mem = NULL;

    try((fd = shm_open(NAME2, FLAGS, MODE)), -1);
    try((mem = mmap(NULL, SIZE, PROT, MAP_SHARED, fd, 0)), MAP_FAILED);
    try(close(fd), -1);

    try((wd = inotify_add_watch(ifd, MEM2, IN_CLOSE_WRITE)), -1);
    try((read(ifd, ebuf, EBUF_SIZE)), -1);

    memcpy(buf, mem, len);
    memset(mem, 0, SIZE);
    try(msync(mem, SIZE, MS_SYNC), -1);
    try(munmap(mem, SIZE), -1);
    try(inotify_rm_watch(ifd, wd), -1);
}

void sendToClient(const void* buf, size_t len)
{
    int fd = 0;
    void* mem = NULL;

#ifdef DEBUG
    writeLog(INFO, "server: sending...");
#endif
    try((fd = shm_open(NAME1, FLAGS, MODE)), -1);
    try((mem = mmap(NULL, SIZE, PROT, MAP_SHARED, fd, 0)), MAP_FAILED);
    try(ftruncate(fd, SIZE), -1);
    try(close(fd), -1);
#ifdef DEBUG
    writeLog(INFO, "server: mapped & closed");
#endif

    memcpy(mem, buf, len);
    try(msync(mem, SIZE, MS_SYNC), -1);
    try(munmap(mem, SIZE), -1);
#ifdef DEBUG
    writeLog(INFO, "server: synced & unmapped");
#endif
}
