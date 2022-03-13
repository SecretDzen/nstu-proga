CC=gcc -std=c11 -D_GNU_SOURCE
CFLAGS=-Wall -Wextra -Werror
TST_LIBS=-lcheck -lm
GCOV_LIBS=--coverage
BUILD_PATH=./
SOURCES=s21_matrix.c
H=s21_matrix.h
LIBO=s21_matrix.o
LIBA=s21_matrix.a
EXE=test.out
SYS=$(shell uname)

all: $(LIBA) test gcov_report

clean:
	rm -rf *.a && rm -rf *.o
	rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov
	rm -rf report/ && rm -rf *.out

test: $(LIBA)
	$(CC) $(CFLAGS) test.c -L. $(LIBA) $(TST_LIBS) -o $(BUILD_PATH)$(EXE)
	$(BUILD_PATH)$(EXE)

rebuild: clean all

$(LIBA): clean
	$(CC) $(CFLAGS) -c $(SOURCES) -o $(BUILD_PATH)$(LIBO)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

gcov_report: $(LIBA)
	$(CC) $(CFLAGS) $(GCOV_LIBS) test.c $(SOURCES) $(LIBA) -L. $(LIBA) $(TST_LIBS) -o $(BUILD_PATH)$(EXE)
	$(BUILD_PATH)$(EXE)
	lcov -t "test" -c -d $(BUILD_PATH) --output-file $(BUILD_PATH)coverage.info
	genhtml $(BUILD_PATH)coverage.info --output-directory $(BUILD_PATH)report/

check:
	@echo ================
	@echo ===STYLE TEST===
	@echo ================
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	@echo ==============
	@echo ===CPPCHECK===
	@echo ==============
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	@echo ================
	@echo ===LEAKS TEST===
	@echo ================
ifeq ($(SYS), Darwin)
	CK_FORK=no leaks -atExit -- $(BUILD_PATH)$(EXE)
else
	CK_FORK=no valgrind --leak-check=full --track-origins=yes ./test.out 
endif
