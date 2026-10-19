CFLAGS = -Wall -Werror -Wextra -std=c11
SOURCES = $(wildcard *_functions/s21_*.c sprintf/s21_sprintf.c)
OBJECTS = $(SOURCES:.c=.o)
TEST_LIBS = -lcheck
OS = $(shell uname)


LIB_NAME = s21_string.a

GCOV_FLAG = --no-external

ifneq ($(OS), Darwin)
        TEST_LIBS = -lcheck -lsubunit -lm
        GCOV_FLAG =
endif


all: $(LIB_NAME)

$(LIB_NAME):
	gcc $(CFLAGS) -c $(SOURCES)
	ar rcs $(LIB_NAME) *.o

test: $(LIB_NAME)
	gcc $(CFLAGS) --coverage $(SOURCES) tests.c $(LIB_NAME) $(TEST_LIBS) -o test
	./test

gcov_report: test
	lcov -o gcov_test.info $(GCOV_FLAG) -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

clean:
	rm -rf ./*.o ./*.a gcov_test ./*.gcno ./*.gcda report/ ./test  ./*.info
	rm -rf coverage_report

style:
	clang-format -style=google $(SOURCES) -n
	clang-format -style=google $(SOURCES) -i
	clang-format -style=google tests.c -n
	clang-format -style=google tests.c -i

rebuild: clean all
