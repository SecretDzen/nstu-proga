CC=g++
CFLAGS=-Wall -Wextra -Werror
BUILD_PATH=build/

l2_test:
	$(CC) $(CFLAGS) 02/test.cpp -o $(BUILD_PATH)prog_l2.out
	$(BUILD_PATH)prog_l2.out

l2:
	$(CC) $(CFLAGS) 02/main.cpp -o $(BUILD_PATH)prog_l2.out
	$(BUILD_PATH)prog_l2.out

l1:
	$(CC) $(CFLAGS) 01/main.cpp -o $(BUILD_PATH)prog_l2.out
	$(BUILD_PATH)lab01.out

clean:
	rm -rf **/*.out

check:
	CK_FORK=no valgrind --leak-check=full --track-origins=yes $(BUILD_PATH)prog_l2.out
