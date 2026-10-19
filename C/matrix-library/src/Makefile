CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TEST_FLAGS = -fprofile-arcs -ftest-coverage -g

SHELLNAME := $(shell uname)
ifeq ($(SHELLNAME), Linux)
  LDFLAGS = -lcheck -lpthread -lm -lsubunit
else ifeq ($(SHELLNAME), Darwin)
  LDFLAGS = -lcheck -lm -lpthread
endif

SRCS = $(filter-out tests/%.c, $(wildcard *.c))
OBJS = $(SRCS:.c=.o)
TEST_SOURCES = $(wildcard tests/*.c)
TEST_OBJS = $(patsubst tests/%.c,tests/%.o,$(TEST_SOURCES))

all: s21_matrix.a

s21_matrix.a: $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) -c $< -o $@

test: CFLAGS += $(TEST_FLAGS)
test: $(TEST_OBJS) s21_matrix.a
	$(CC) $(CFLAGS) $(TEST_OBJS) s21_matrix.a $(LDFLAGS) -o $@
	./$@

gcov_report: clean test
	mkdir -p gcov_html
	lcov -t 'Report' -c -d . --output-file gcov_html/coverage.info --exclude "*/tests/*"
	genhtml gcov_html/coverage.info --output-directory gcov_html/
	xdg-open gcov_html/index.html || open gcov_html/index.html || true

clean:
	rm -rf $(OBJS) $(TEST_OBJS) s21_matrix.a *.gcno *.gcda *.gcov test tests/*.gcno tests/*.gcda tests/*.gcov gcov_html