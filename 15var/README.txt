To run lab1:
    gcc lab1.c && ./a.out input1.txt 2

To run static lab2:
	gcc -c convert.c -o convert.o
	ar rcs libconvert.a convert.o
	gcc lab02s.c -lm -L. -lconvert -o lab02s
	./lab02s input1.txt 2

To run lab02d:
	gcc -fPIC -c convert.c -o convert.o &&
	gcc -shared -o libconvert.so convert.o &&
	gcc lab02d.c -ldl -o lab02d &&
	./lab02d input2.txt 2

Set up LD_LIBRARY_PATH:
    sudo find /home -name libconvert.so
    LD_LIBRARY_PATH=~/path/from/find

Repeat running lab2

To run lab3: Run lab02d
    gcc lab03.c -o lab03
	./lab03 input1.txt input2.txt 4
