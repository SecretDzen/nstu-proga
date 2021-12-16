#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define DL_PATH "libconvert.so"
#define BUF_SIZE 256
#define OUTPUT_F "output"

pthread_t *threads;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

size_t *replaces;
int processed = 0;
int exchangeCount = 0;
char ch = '1';

static void *file_processing(void *arg);

int main(int argc, char **argv) {
  int files_num = argc - 1;
  exchangeCount = atoi(argv[files_num]);
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
  char *filename = (char *)arg;
  int inputFd, outputFd, openFlags;
  mode_t filePerms;

  char f_out_name[BUF_SIZE] = {0};
  char buf[BUF_SIZE] = {0};
  char ch;

  void *dl_handle;
  dl_handle = dlopen(DL_PATH, RTLD_LAZY);

  if (!dl_handle) {
    printf("Wild Library Open Error appeared!\nError: %s\n", dlerror());
    exit(-1);
  }

  void (*nameGenerator)(char *argument, char file[20]);
  nameGenerator = dlsym(dl_handle, "nameGenerator");
  if (nameGenerator == NULL) {
    printf("Wild Library Connection Error appeared! Error: %s\n", dlerror());
    exit(-1);
  }

  inputFd = open(filename, O_RDONLY);
  if (inputFd < 0) {
    printf("Error %d (%s) while open file: %s!\n", errno, strerror(errno), filename);
    exit(-1);
  }

  nameGenerator(filename, f_out_name);
  int i = 0;
  while (read(inputFd, &ch, 1) > 0) {
    buf[i] = ch;
    i++;
  }
  close(inputFd);

  int (*convert)(char *str, int last, int exchangeCount);
  convert = dlsym(dl_handle, "convert");

  if (convert == NULL) {
    printf("Wild Library Connection Error appeared! Error: %s\n", dlerror());
    exit(-1);
  }

  int last = strlen(buf) - 1;
  int spaces = (last == 59) ? 5 : 8;
  convert(buf, last, exchangeCount);

  replaces[processed] = spaces;

  pthread_mutex_lock(&mtx);
  processed++;
  pthread_mutex_unlock(&mtx);
  pthread_cond_signal(&cond);

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  outputFd = open(f_out_name, openFlags, filePerms);
  if (outputFd == -1) {
    printf("Error(%d): %s\nWith file: %s\n ", errno, strerror(errno),
           f_out_name);
    exit(-1);
  }

  if (write(outputFd, buf, strlen(buf)) <= 0) {
    printf("Write error\nError: %d - %s\n", errno, strerror(errno));
    exit(-1);
  }

  close(outputFd);

  return (void *)NULL;
}
