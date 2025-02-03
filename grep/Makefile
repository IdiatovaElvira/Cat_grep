SHELL := /bin/bash
CC = gcc
FLAGS = -std=c11 -Wall -Wextra -Werror 
FILE = file1.txt file2.txt
EXECNAME = s21_grep

SRCS = s21_grep.c process_file.c grep_option.c
OBJECT_FILES = s21_grep.o process_file.o grep_option.o

all: $(EXECNAME) tests

rebuild: clean $(EXECNAME)

$(EXECNAME): $(OBJECT_FILES)
	$(CC) $(FLAGS) $(OBJECT_FILES) -o $(EXECNAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@


tests: 
	-diff <(./$(EXECNAME) '^T' $(FILE)) <(grep '^T' $(FILE))
	-diff <(./$(EXECNAME) -e grep -e "test" $(FILE)) <(grep -e grep -e "test" $(FILE))
	-diff <(./$(EXECNAME) -i grep $(FILE)) <(grep -i grep $(FILE))
	-diff <(./$(EXECNAME) -v grep $(FILE)) <(grep -v grep $(FILE))
	-diff <(./$(EXECNAME) -c grep $(FILE)) <(grep -c grep $(FILE))
	-diff <(./$(EXECNAME) -l grep $(FILE)) <(grep -l grep $(FILE))
	-diff <(./$(EXECNAME) -n grep $(FILE)) <(grep -n grep $(FILE))
	-diff <(./$(EXECNAME) -n grep $(FILE)) <(grep -n grep $(FILE))
	-diff <(./$(EXECNAME) -s "." file_notExisting.txt) <(grep -s "." file_notExisting.txt)
	-diff <(./$(EXECNAME) -h grep $(FILE)) <(grep -h grep $(FILE))
	-diff <(./$(EXECNAME) -o grep $(FILE)) <(grep -o grep $(FILE))
	-diff <(./$(EXECNAME) -f file4.txt $(FILE)) <(grep -f file4.txt $(FILE))

clean:
	# rm -f $(OBJECT_FILES) $(EXECNAME)
	rm -f *.o $(EXECNAME)

checks:
	clang-format -n *.c
	clang-format -n *.h

leaks:
	valgrind --tool=memcheck --leak-check=yes  ./$(EXECNAME) -e "grep" -e "test" $(FILE)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

fix:
	clang-format -i *.c
	clang-format -i *.h
