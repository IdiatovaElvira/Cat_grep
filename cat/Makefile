SHELL := /bin/bash
CC = gcc
FLAGS = -std=c11 -Wall -Wextra -Werror
FILE = file.txt file2.txt
EXECNAME = s21_cat
all: s21_cat tests

rebuild: clean s21_cat

s21_cat: s21_cat.c
	$(CC) $(FLAGS) s21_cat.c -o $(EXECNAME)

tests: 
	-diff <(./$(EXECNAME) $(FILE)) <(cat $(FILE))
	-diff <(./$(EXECNAME) -b $(FILE)) <(cat -b $(FILE))
	-diff <(./$(EXECNAME) -e $(FILE)) <(cat -e $(FILE))
	-diff <(./$(EXECNAME) -be $(FILE)) <(cat -be $(FILE))
	-diff <(./$(EXECNAME) -n $(FILE)) <(cat -n $(FILE))
	-diff <(./$(EXECNAME) -s $(FILE)) <(cat -s $(FILE))
	-diff <(./$(EXECNAME) -t $(FILE)) <(cat -t $(FILE))
	-diff <(./$(EXECNAME) -v $(FILE)) <(cat -v $(FILE))
	-diff <(./$(EXECNAME) --number-nonblank $(FILE)) <(cat --number-nonblank $(FILE))
	-diff <(./$(EXECNAME) --number $(FILE)) <(cat --number $(FILE))
	-diff <(./$(EXECNAME) --squeeze-blank $(FILE)) <(cat --squeeze-blank $(FILE))

clean:
	rm -rf *.o *.a $(EXECNAME)

checks:
	clang-format -n *.c
	clang-format -n *.h
leaks:
	valgrind --tool=memcheck --leak-check=yes  ./$(EXECNAME)
cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

fix:
	clang-format -i *.c
	clang-format -i *.h