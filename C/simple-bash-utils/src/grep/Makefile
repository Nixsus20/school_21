CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep: s21_grep.c
	$(CC) $(FLAGS) s21_grep.c -o s21_grep

clean:
	rm -f s21_grep

rebuild: clean all

chmod:
	chmod +x test_grep.sh

test: s21_grep chmod 
	sh test_grep.sh || exit 1