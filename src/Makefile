CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 
HEADERS = $(wildcard controller/*.h model/*h)
SOURCES = $(wildcard controller/*.cc model/*.cc)
OBJECTS = $(SOURCES:.cc=.o)
TEST_SOURCES = $(wildcard tests/*.cc)
NAME_TEST = tests
TEST_OBJECTS = $(TEST_SOURCES:.cc=.o)
PROJECT = s21_calculator
EXECUTABLE = s21_test
OS = $(shell uname)
REPORT = report
INSTALL_DIR = build
DOXYGEN = doxygen
DOCS_DIR = docs/
Doxyfile = Doxyfile
DOCS_PATH = ../docs/html/index.html

ifeq ($(OS), Linux)
	LIBS = $(shell pkg-config --cflags --libs gtest) -lgtest_main
    OPEN_APPLICATION = xdg-open
	PATH_OPEN = build/
endif
ifeq ($(OS), Darwin)
	LIBS = -lgtest -lgmock -pthread
	OPEN_APPLICATION = open
	PATH_OPEN = build/view.app
endif

all: $(PROJECT).a tests 

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

$(PROJECT).a: $(OBJECTS)
	ar rcs $@ $^
	ranlib $@

tests: $(PROJECT).a $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -L. $(PROJECT).a $(LIBS) -o $(EXECUTABLE)
	@./$(EXECUTABLE)

install:
	mkdir $(INSTALL_DIR) 
	cd $(INSTALL_DIR) && qmake ../view && make all 

uninstall: 
	rm -rf $(INSTALL_DIR)

dist:
	mkdir -p ../dist
	cp -r ../src/* ../dist/
	zip -r ../CPP_SmartCalc.zip * ../dist
	rm -rf ../dist

dvi: $(Doxyfile)
	$(DOXYGEN) $(Doxyfile)
	open $(DOCS_PATH)

open:
	$(OPEN_APPLICATION) $(PATH_OPEN)

gcov_report: $(SOURCES) $(TEST_SOURCES)
	$(CC) $(CFLAGS) --coverage $(SOURCES) -L. $(TEST_SOURCES) $(PROJECT).a $(LIBS) -o $(EXECUTABLE)
	@./$(EXECUTABLE)
	lcov --no-external -t "$(PROJECT)" -o $(PROJECT).info -c -d . --ignore-errors inconsistent --exclude "*/*.h"
	genhtml --ignore-errors inconsistent -o $(REPORT) $(PROJECT).info
	@$(OPEN_APPLICATION) $(REPORT)/index.html

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n -style=Google $(SOURCES) $(TEST_SOURCES) $(HEADERS)
	rm -rf .clang-format

leak_check:
	CK_FORK=no leaks -atExit -- ./$(EXECUTABLE)

valgrind_check:
	CK_FORK=no valgrind --leak-check=full ./$(EXECUTABLE)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ $(SOURCES) $(TEST_SOURCES) $(HEADERS)

clean:
	rm -rf controller/*.o model/*.o *.a
	rm -rf *.info *.gcno *.gcda s21_test tests/*.o tests/*.gcno tests/*.gcda report ../docs

style_correct:
	cp ../materials/linters/.clang-format .
	clang-format -i -style=Google $(SOURCES) $(TEST_SOURCES) $(HEADERS)
	rm -rf .clang-format