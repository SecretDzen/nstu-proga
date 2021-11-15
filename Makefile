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

all: $(LAB_1) clean $(LAB_2s) clean $(LAB_2d) clean $(LAB_3)

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

$(LAB_3):
	$(CC) $(CFLAGS) $(PATH_3)$(MAIN) -o $(B_PATH)$(LAB_3)
	$(B_PATH)$(LAB_3) ./lab3/input1.txt $(PATH_3)input2.txt 4
