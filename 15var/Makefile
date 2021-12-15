clean:
	rm -rf *.out
	rm -rf *.o
	rm -rf *.so

LD_PATH:
    # $(shell LD_LIBRARY_PATH=$(LD))
	# shell export LD_LIBRARY_PATH

lab1:
	gcc lab1.c
	./a.out input1.txt 2

lab2s:
	gcc -c convert.c -o convert.o
	ar rcs libconvert.a convert.o
	gcc lab02s.c -lm -L. -lconvert -o lab02s
	./lab02s ex1.txt 2

lab2d:
	gcc -fPIC -c convert.c -o convert.o
	gcc -shared -o libconvert.so convert.o
	gcc lab02d.c -ldl -o lab02d
	./lab02d ex2.txt 2

lab3: clean lab2d
	gcc lab03.c -o lab03
	./lab03 ex1.txt ex2.txt 4

lab4: clean lab2d
	gcc lab04serv.c -o serv_04
	gcc lab04cli.c -o cli_04

serv04:
	./serv_04

cli04:
	./cli_04 ex1.txt ex2.txt 6

lab5: clean lab2d
	gcc -L. -lrt lab05serv.c -o serv_05
	gcc -L. -lrt lab05cli.c -o cli_05

serv05:
	./serv_05

cli05:
	./cli_05 ex1.txt ex2.txt 6

lab6: clean lab2d
	gcc -L. -lpthread -lrt lab06serv.c -o serv_06
	gcc -L. -lpthread -lrt lab06cli.c -o cli_06

serv06:
	./serv_06

cli06:
	./cli_06 ex1.txt ex2.txt 6

