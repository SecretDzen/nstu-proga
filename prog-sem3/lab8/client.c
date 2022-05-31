#include "tools.h"

void send_files(const int sock, char** files, const int files_count);

int main(int argc, char** argv) {
  struct sockaddr_in addr;
  int sockfd = 0;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("%s\n", strerror(errno));
    exit(-1);
  }

  if (inet_pton(AF_INET, HOST, &addr.sin_addr) <= 0) {
    printf("inet_pton error: %s\n", strerror(errno));
    exit(-1);
  }

  connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
  send_files(sockfd, (argv + 1), argc);

  for (int n = 0; n < argc - 1; n++) {
    int len = 0;
    ssize_t bytes = 0;
    char buf[BUF_SIZE] = {0};

    read(sockfd, &len, sizeof(len));

    bytes = read(sockfd, buf, len);
    if (bytes == -1) {
      printf("%s\n", strerror(errno));
      exit(-1);
    }

    printf("Server response. Size: %ld. Message: %s\n", bytes, buf);
  }
  close(sockfd);

  return 0;
}

void send_files(const int sock, char** files, const int files_count) {
  write(sock, &files_count, sizeof(files_count));

  for (int n = 0; n < files_count - 1; n++) {
    int len = strlen(files[n]);

    write(sock, &len, sizeof(len));
    write(sock, files[n], len);

    printf("Text to send: %s\n", files[n]);
  }
}