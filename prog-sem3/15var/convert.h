#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 256

void convert(char *str, int last, int exchangeCount);
void nameGenerator(char *argument, char file[20]);