#include "lab08.h"

#define LAB2_PATH "./lab02d"
#define LAB2_NAME "lab02d"
#define MAX_FILES 16
#define MAX_NAME 255

int get_files(const int connfd, char*** files);
char* process_file(const char* file, const char* spaces);

int main() {
  struct sockaddr_in addr;
  int files_count = 0;
  int listenfd = 0;
  int connfd = 0;
  char** files;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd == -1) {
    printf("%s\n", strerror(errno));
    exit(-1);
  }

  bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
  listen(listenfd, 10);

  connfd = accept(listenfd, NULL, NULL);
  if (connfd == -1) {
    printf("%s\n", strerror(errno));
    exit(-1);
  }

  files_count = get_files(connfd, &files);
    
  for (int n = 0; n < files_count - 2; n++) {
    printf("%s - %s processing...\n", files[n], files[files_count - 2]);

    char* msg = process_file(files[n], files[files_count - 2]);
    int len = strlen(msg);

    write(connfd, &len, sizeof(len));
    write(connfd, msg, len);
    free(msg);
  }

  close(connfd);
  return 0;
}

int get_files(const int sock, char*** files) {
  int files_count = 0;

  *files = calloc(sizeof(char*), MAX_FILES);
  read(sock, &files_count, sizeof(files_count));

  for (int n = 0; n < files_count - 1; n++) {
    int len = 0;
    ssize_t bytes = 0;

    (*files)[n] = calloc(sizeof(char), MAX_NAME);
    read(sock, &len, sizeof(len));

    bytes = read(sock, (*files)[n], len);
    if (bytes == -1) {
      printf("%s\n", strerror(errno));
      exit(-1);
    }

    printf("Client send text. Size: %ld Inners: %s\n", bytes, (*files)[n]);

    if (bytes == 0) free((*files)[n]);
  }

  return files_count;
}

char* process_file(const char* file, const char* spaces) {
  pid_t pid;
  int status;
  char* restrict result_msg = calloc(sizeof(char), BUF_SIZE);

  pid = fork();
  if (pid == -1) {
    printf("%s\n", strerror(errno));
    exit(-1);
  }

  if (pid == 0) {
    execl(LAB2_PATH, LAB2_NAME, file, spaces, NULL);
  } else if (pid > 0) {
    int child = wait(&status);

    if (child > 0) {
      int len = sprintf(result_msg, "child's done with: %d\n", status);

      if (len < 0) {
        printf("%s\n", strerror(errno));
        exit(-1);
      }

    } else if (child == -1) {
      printf("%s\n", strerror(errno));
      exit(-1);
    }
  }
  return result_msg;
}