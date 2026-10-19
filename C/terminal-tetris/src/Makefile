SHELLNAME := $(shell uname)
ifeq ($(SHELLNAME), Linux)
  LDFLAGS = -lcheck -lpthread -lm -lsubunit -lncurses
else ifeq ($(SHELLNAME), Darwin)
  LDFLAGS = -lcheck -lm -lpthread -lncurses
endif


CC = gcc
CFLAGS = -Wall -Wextra -g -lncurses

TETRIS_SRC = brick_game/tetris/game.c brick_game/tetris/code.c gui/cli/interface.c

HEADERS = game.h gameInfo.h brick_game/tetris/code.h gui/cli/interface.h

TARGET = tetris

TEST_TARGET = test_runner
TEST_SRC = test.c brick_game/tetris/code.c gui/cli/interface.c

GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# Переменные установки
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
DESTDIR ?=

PACKAGE = tetris
VERSION = 1.0
DIST_DIR = $(PACKAGE)-$(VERSION)

.PHONY: all install uninstall dvi dist

all: $(TARGET)

$(TARGET): $(TETRIS_SRC) $(HEADERS)
	$(CC) $(TETRIS_SRC) -o $(TARGET) $(CFLAGS)

$(TEST_TARGET): $(TEST_SRC) $(HEADERS)
	$(CC) $(TEST_SRC) -o $(TEST_TARGET) $(CFLAGS) $(GCOV_FLAGS) $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

gcov_report: clean test
	mkdir -p gcov_html
	lcov -t 'Report' -c -d . --output-file gcov_html/coverage.info --exclude "$(shell pwd)/test.c" --exclude "$(shell pwd)/gui/cli/*"
	genhtml gcov_html/coverage.info --output-directory gcov_html/
	xdg-open gcov_html/index.html || open gcov_html/index.html || true

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o brick_game/tetris/*.o gui/cli/*.o *.gcda *.gcno *.gcov
	rm -rf gcov_html
	rm -rf $(DIST_DIR) $(DIST_DIR).tar.gz


install: $(TARGET)
	mkdir -p $(DESTDIR)$(BINDIR)
	install -m 0755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)


dvi:
	@echo "dvi documentation target is not implemented (no Texinfo)"


dist:
	rm -rf $(DIST_DIR)
	mkdir -p $(DIST_DIR)
	cp -r brick_game gui *.h *.c Makefile $(DIST_DIR)
	tar -czf $(DIST_DIR).tar.gz $(DIST_DIR)
