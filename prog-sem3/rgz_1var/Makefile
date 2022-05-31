.PHONY=all var_func proceed_file server client
CC=gcc
CLAGS=-Wall -Wextra -Werror

all: clean var_func proceed_file server client
	clear

clean:
	rm -rf *.o && rm -rf *.so && rm -rf *.out
	rm -rf *.log
	rm -rf proceed_file
	rm -rf server && rm -rf client
	clear

server:
	$(CC) $(CFLAGS) server.c log_writer.c -o server

client:
	$(CC) $(CFLAGS) client.c log_writer.c -o client 

var_func:
	$(CC) var_func.c -o var_func.o -c -fPIC
	$(CC) var_func.o -o var_func.so -shared

proceed_file:
	$(CC) $(CFLAGS) proceed_file.c log_writer.c -o proceed_file -ldl
