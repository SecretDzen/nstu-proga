#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define DL_PATH "libreadFile.so"
#define BUF_SIZE 256
#define OUTPUT_F "output"

pthread_t *threads;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

size_t *replaces;
int processed = 0;
int toDelete = 0;
char ch = '1';

static void *file_processing(void *arg);

int main(int argc, char **argv) {
  int files_num = argc - 1;
  toDelete = atoi(argv[files_num]);
  threads = calloc(files_num, sizeof(pthread_t));
  replaces = calloc(files_num, sizeof(int));

  for (int num = 1; num < argc - 1; num++) {
    pthread_create(&threads[num - 1], NULL, file_processing, argv[num]);
    pthread_join(threads[num - 1], NULL);
  }

  while (processed != (argc - 2)) {
    pthread_cond_wait(&cond, &mtx);
  }

  for (int num = 0; num < processed; num++) {
    printf("thread[%d] returns %jd\n", num, replaces[num]);
  }

  free(threads);
  free(replaces);

  return 0;
}

static void *file_processing(void *arg) {
  const char *filename = (char *)arg;
  int outputFd, openFlags;
  mode_t filePerms;

  char fileName2[BUF_SIZE] = {0};

  char buf[BUF_SIZE] = {0};
  char new_buf[BUF_SIZE] = {0};

  void *dl_handle;
  int (*readFile)(const char *fp, char *str);

  dl_handle = dlopen(DL_PATH, RTLD_LAZY);
  if (!dl_handle) {
    printf("Wild Library Open Error appeared!\nError: %s\n", dlerror());
    exit(-1);
  }

  readFile = dlsym(dl_handle, "readFile");
  if (readFile == NULL) {
    printf("Wild Library Connection Error appeared! Error: %s\n", dlerror());
    exit(-1);
  }

  int charNums = readFile(filename, buf);
  int spaces = 0;

  if (toDelete < 0) {
    printf("Expected positive number of spaces\n");
    exit(-1);
  }

  for (int i = 0; i < charNums; i++) {
    if (buf[i] == ' ' && spaces < toDelete)
      spaces++;
    else
      new_buf[i - spaces] = buf[i];
  }

  replaces[processed] = spaces;

  pthread_mutex_lock(&mtx);
  processed++;
  pthread_mutex_unlock(&mtx);
  pthread_cond_signal(&cond);
  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  sprintf(fileName2, "./build/input%c.text", ch);
  ch += 1;
  outputFd = open(fileName2, openFlags, filePerms);

  if (outputFd == -1) {
    printf("Error opening file %s\n ", fileName2);
    exit(-1);
  }

  if (write(outputFd, new_buf, strlen(new_buf)) <= 0) {
    printf("Wild Error Appear!\nError: %d - %s\n", errno, strerror(errno));
    close(outputFd);
    exit(-1);
  }

  close(outputFd);

  return (void *)NULL;
}
