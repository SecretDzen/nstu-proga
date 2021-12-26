CFLAGS= -lrt
SERVICE=avt019-17.service

all: clean spaced_48 prog client server
	cp ./$(SERVICE) /etc/systemd/system/$(SERVICE)
	sudo systemctl daemon-reload
	clear

server:
	gcc $(CFLAGS) server.c log.c -o server

client:
	gcc $(CFLAGS) client.c log.c -o client 

prog:
	gcc prog.c log.c -o prog -ldl

spaced_48:
	gcc spaced_48.c -o spaced_48.o -c -fPIC
	gcc spaced_48.o -o spaced_48.so -shared

clean:
	rm -f prog
	rm -f spaced_48.o
	rm -f spaced_48.so
	rm -f spaced_48
	rm -f prog
	rm -f client
	rm -f server
	rm -f /dev/shm/test1
	rm -f /dev/shm/test2
	rm -f OUTPUT_*
	rm -f *.log
	rm -f /etc/systemd/system/$(SERVICE)
