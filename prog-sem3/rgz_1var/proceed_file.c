#include "tools.h"

int main(int argc, char** argv) {
  int fd = 0, char_replaced = 0;
  ssize_t bytes = 0;
  char file[BUF] = {0};
  char out_file[BUF] = {0};

  int len = strlen(argv[2]);

  if (len > 1) {
    log_writer(ERROR, "Not a char proceeded\n");
    exit(-1);
  }

  char to_delete = argv[2][len - 1];

  void* dl_handle;
  int (*var_func)(char*, char);

  try((fd = open(argv[1], O_RDONLY)), ERROR);
  try((bytes = read(fd, file, BUF - 1)), ERROR);
  try(close(fd), ERROR);

  if ((dl_handle = dlopen("./var_func.so", RTLD_LAZY)) == NULL) {
    log_writer(ERROR, dlerror());
    exit(-1);
  }

  if ((var_func = dlsym(dl_handle, "var_func")) == NULL) {
    log_writer(ERROR, dlerror());
    exit(-1);
  }
  char log_start[BUF] = {0};
  snprintf(log_start, BUF - 1, "Starting file: %s", argv[1]);
  log_writer(OK, log_start);
  char_replaced = var_func(file, to_delete);

  if (dlclose(dl_handle) != 0) {
    log_writer(ERROR, dlerror());
    exit(-1);
  }

  if (char_replaced == ERROR) {
    char logs[BUF] = {0};
    snprintf(logs, BUF - 1, "Cannot proceed: %s\n", argv[1]);
    log_writer(ERROR, logs);
  }

  snprintf(out_file, BUF - 1, "%s.out", argv[1]);
  int len_out = strlen(file);
  try((fd = open(out_file, O_FLAGS, 0666)), ERROR);
  try(write(fd, file, len_out), ERROR);
  try(close(fd), ERROR);

  return char_replaced;
}
