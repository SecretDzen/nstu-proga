CC=gcc
CFLAGS=-Wall -Wextra -Werror
MAIN=main.c
B_PATH=./build/

LIB=ar rcs

LAB_1=lab_1
PATH_1=./lab1/

LAB_2s=lab_2s
LAB_2d=lab_2d
STATIC=static.c
DYNAMIC=dynamic.c
PATH_2=./lab2/

LAB_3=lab_3
PATH_3=./lab3/

LAB_4=lab_4
LAB_4s=lab_4s
LAB_4c=lab_4c
PATH_4=./lab4/

LAB_5=lab_5
LAB_5s=lab_5s
LAB_5c=lab_5c
PATH_5=./lab5/

LAB_6=lab_6
LAB_6s=lab_6s
LAB_6c=lab_6c
PATH_6=./lab6/

all: $(LAB_1) clean $(LAB_2s) clean $(LAB_2d) $(LAB_3) $(LAB_4s)

clean:
	rm -rf $(B_PATH)lab_*
	rm -rf ./**/*.text
	rm -rf ./**/*o && rm -rf ./**/*.a

rebuild: clean all

push: clean
	git add .
	git status
	git commit -m "$m"
	git push origin $b

$(LAB_1):
	$(CC) $(CFLAGS) $(PATH_1)$(MAIN) -lm -o $(B_PATH)$(LAB_1)
	$(B_PATH)$(LAB_1) $(PATH_1)input.txt 4

$(LAB_2s):
	$(CC) $(CFLAGS) -c $(PATH_2)readFile.c -o $(PATH_2)readFile.o
	$(LIB) $(PATH_2)libreadFile.a $(PATH_2)readFile.o
	$(CC) $(CFLAGS) $(PATH_2)$(STATIC) -lm -L$(PATH_2) -lreadFile -o $(B_PATH)$(LAB_2s)
	$(B_PATH)$(LAB_2s) $(PATH_2)input.txt 4

$(LAB_2d): clean
	$(CC) -fPIC -c $(PATH_2)readFile.c -o $(PATH_2)readFile.o
	$(CC) -shared -o $(PATH_2)libreadFile.so $(PATH_2)readFile.o
	$(CC) $(CFLAGS) $(PATH_2)$(DYNAMIC) -ldl -o $(B_PATH)$(LAB_2d)
	$(B_PATH)$(LAB_2d) $(PATH_2)input1.txt 4

$(LAB_3): $(LAB_2d)
	$(CC) $(CFLAGS) $(PATH_3)$(MAIN) -o $(B_PATH)$(LAB_3)
	$(B_PATH)$(LAB_3) $(PATH_3)input1.txt $(PATH_3)input2.txt 4

$(LAB_4): $(LAB_2d)
	$(CC) $(CFLAGS) $(PATH_4)server.c -o $(B_PATH)$(LAB_4s)
	$(CC) $(CFLAGS) $(PATH_4)client.c -o $(B_PATH)$(LAB_4c)

server:
	$(B_PATH)$(LAB_4s)

client:
	$(B_PATH)$(LAB_4c) $(PATH_3)input1.txt $(PATH_3)input2.txt 4

$(LAB_5): $(LAB_2d)
	$(CC) $(CFLAGS) -L. -lrt $(PATH_5)server.c -o $(B_PATH)$(LAB_5s)
	$(CC) $(CFLAGS) -L. -lrt $(PATH_5)client.c -o $(B_PATH)$(LAB_5c)

server5:
	$(B_PATH)$(LAB_5s)

client5:
	$(B_PATH)$(LAB_5c) $(PATH_3)input1.txt $(PATH_3)input2.txt 4

$(LAB_6): $(LAB_2d)
	$(CC) $(CFLAGS) -L. -lpthread -lrt $(PATH_6)server.c -o $(B_PATH)$(LAB_6s)
	$(CC) $(CFLAGS) -L. -lpthread -lrt $(PATH_6)client.c -o $(B_PATH)$(LAB_6c)

server6:
	$(B_PATH)$(LAB_6s)

client6:
	$(B_PATH)$(LAB_6c) $(PATH_3)input1.txt $(PATH_3)input2.txt 4

lab_7: $(LAB_2d)
	gcc $(CFLAGS) lab7/main.c -ldl -pthread -o build/lab_7
	./build/lab_7 $(PATH_3)input1.txt $(PATH_3)input2.txt 8

pack_8:
	gcc $(CFLAGS) lab8/server.c -o build/server
	gcc $(CFLAGS) lab8/client.c -o build/client

cli_8:
	./build/client $(PATH_3)input1.txt $(PATH_3)input2.txt 6

serv_8:
	./build/server
