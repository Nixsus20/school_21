#!/bin/bash

# Компилируем s21_cat
gcc -o s21_cat s21_cat.c

# Создаем временный файл для тестирования
echo -e "Line 1\nLine 2\n\nLine 4\n\n\nLine 7" > test_file.txt

# Функция для сравнения вывода s21_cat и cat
compare_output() {
    flag=$1
    echo "Testing flag: $flag"
    ./s21_cat $flag test_file.txt > s21_output.txt
    cat $flag test_file.txt > cat_output.txt
    if diff s21_output.txt cat_output.txt; then
        echo "Test passed for flag $flag"
    else
        echo "Test failed for flag $flag"
    fi
    echo "------------------------"
}

# Тестируем различные флаги
compare_output "-b"
compare_output "-n"
compare_output "-s"
compare_output "-e"
compare_output "-t"
compare_output "-v"

# Очищаем временные файлы
rm test_file.txt s21_output.txt cat_output.txt