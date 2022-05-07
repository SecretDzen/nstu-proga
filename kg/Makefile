CC=gcc
CD=nvcc
FLAGS=-Wall -Wextra -Werror
BUILD_PATH=build/

l2:
	$(CD) 02/sample.cu -o $(BUILD_PATH)prog_l2.out -ccbin "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64"
	$(BUILD_PATH)prog_l2.out > $(BUILD_PATH)data2.txt
	sed 's/\./,/g' $(BUILD_PATH)data2.txt > $(BUILD_PATH)result2.txt

l1_valya:
	$(CC) $(FLAGS) 01_Valya/main.c -o $(BUILD_PATH)prog_l1_v.out -lm
	$(BUILD_PATH)prog_l1_v.out
	sed 's/\./,/g' $(BUILD_PATH)data.txt > $(BUILD_PATH)result.txt

l1:
	$(CC) $(FLAGS) 01/main.c -o $(BUILD_PATH)prog_l1.out -lm
	$(BUILD_PATH)prog_l1.out
	sed 's/\./,/g' $(BUILD_PATH)data.txt > $(BUILD_PATH)result.txt

clean:
	rm -rf **/*.txt
	rm -rf **/*.out && rm -rf **/*.exp && rm -rf **/*.lib

