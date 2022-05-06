CC=gcc
FLAGS=-Wall -Wextra -Werror
BUILD_PATH=build/


l1_valya:
	$(CC) $(FLAGS) 01_Valya/main.c -o $(BUILD_PATH)prog_l1_v.out -lm
	$(BUILD_PATH)prog_l1_v.out

l1:
	$(CC) $(FLAGS) 01/main.c -o $(BUILD_PATH)prog_l1.out -lm
	$(BUILD_PATH)prog_l1.out
	sed 's/\./,/g' $(BUILD_PATH)data.txt > $(BUILD_PATH)result.txt

clean:
	rm -rf **/*.txt
	rm -rf **/*.out
