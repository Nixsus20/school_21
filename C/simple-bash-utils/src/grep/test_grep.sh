#!/bin/bash

# Путь к вашей программе s21_grep
S21_GREP=./s21_grep

# Проверяем, что s21_grep существует и исполняемый
if [ ! -x "$S21_GREP" ]; then
    echo "Ошибка: Файл $S21_GREP не найден или не является исполняемым."
    exit 1
fi

# Создаем временные файлы для тестирования
FILE1="file1.txt"
FILE2="file2.txt"
PATTERNS="patterns.txt"

# Создаем тестовые файлы
echo -e "Hello World\nThis is a test file.\nGREP is useful.\n123 test line.\nAnother line." > $FILE1
echo -e "Another test file.\nhello again.\ngrep can search.\nTest line with numbers 12345.\nEnd of file." > $FILE2
echo -e "hello\ntest\n[0-9]+" > $PATTERNS

# Массив с тестовыми случаями, включая комбинации флагов
tests=(
    # Одиночные флаги
    "-e Hello $FILE1"
    "-i grep $FILE1"
    "-v test $FILE1"
    "-c test $FILE1"
    "-l hello $FILE1 $FILE2"
    "-n is $FILE1"
    "-h hello $FILE1 $FILE2"
    "-s hello nonexistent.txt"
    "-f $PATTERNS $FILE1"
    "-o is $FILE1"

    # Комбинации флагов
    "-i -n grep $FILE1 $FILE2"
    "-v -c test $FILE1"
    "-e ^Hello -v $FILE1"
    "-i -h hello $FILE1 $FILE2"
    "-c -l test $FILE1 $FILE2"
    "-l -v hello $FILE1 $FILE2"
    "-n -i -v grep $FILE1 $FILE2"
    "-c -h test $FILE1 $FILE2"
)

# Счетчики
total_tests=0
passed_tests=0

# Функция для сравнения результатов
run_test() {
    ((total_tests++))
    test_case="$1"
    echo "Тест $total_tests: ./s21_grep $test_case"

    # Запускаем оригинальный grep
    grep $test_case > grep_output.txt 2> grep_error.txt
    grep_exit_code=$?

    # Запускаем s21_grep
    $S21_GREP $test_case > s21_output.txt 2> s21_error.txt
    s21_exit_code=$?

    # Сравниваем коды выхода
    if [ $grep_exit_code -ne $s21_exit_code ]; then
        echo "❌ Не совпадает код выхода. Ожидалось $grep_exit_code, получено $s21_exit_code"
        return
    fi

    # Сравниваем выводы
    diff -q grep_output.txt s21_output.txt > /dev/null
    output_diff=$?

    diff -q grep_error.txt s21_error.txt > /dev/null
    error_diff=$?

    if [ $output_diff -ne 0 ] || [ $error_diff -ne 0 ]; then
        echo "❌ Вывод не совпадает с оригинальным grep."
        echo "Оригинальный grep вывод:"
        cat grep_output.txt
        echo "Ошибки оригинального grep:"
        cat grep_error.txt
        echo "Ваш s21_grep вывод:"
        cat s21_output.txt
        echo "Ошибки вашего s21_grep:"
        cat s21_error.txt
    else
        echo "✅ Тест пройден успешно."
        ((passed_tests++))
    fi
}

# Запускаем все тесты
for test_case in "${tests[@]}"; do
    run_test "$test_case"
    echo "-----------------------------"
done

# Удаляем временные файлы
rm -f $FILE1 $FILE2 $PATTERNS grep_output.txt grep_error.txt s21_output.txt s21_error.txt

# Итог
echo "Тестирование завершено. Пройдено $passed_tests из $total_tests тестов."

# Возвращаем соответствующий код выхода
if [ $passed_tests -eq $total_tests ]; then
    exit 0
else
    exit 1
fi
