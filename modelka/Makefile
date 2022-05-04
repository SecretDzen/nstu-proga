CC=g++
B_PATH=build/

lab5:
	$(CC) 05/main.cpp -o ${B_PATH}05.out
	${B_PATH}05.out >> ${B_PATH}raw_data.txt
	rm -rf ${B_PATH}*.out
	sed 's/\./,/g' ${B_PATH}raw_data.txt > ${B_PATH}result.txt

lab1:
	${CC} 01/main.cpp -o ${B_PATH}01.out
	${B_PATH}01.out
	rm -rf ${B_PATH}*.out