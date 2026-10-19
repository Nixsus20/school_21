CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11

all: s21_cat

s21_cat: s21_cat.c
	$(CC) $(FLAGS) s21_cat.c -o s21_cat

clean:
	rm -f s21_cat

rebuild: clean all

chmod:
	chmod +x test_s21_cat.sh

test: s21_cat chmod 
	sh test_s21_cat.sh || exit 1