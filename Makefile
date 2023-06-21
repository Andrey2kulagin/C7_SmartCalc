CC = gcc
CFLAG = -Wall -Wextra -Werror
APP = build/s21_calc.app
BACKEND_FILES = source/c_libs.c;
BACKEND_FILES_O = c_libs.o
LIBS := -lcheck -lm
TESTS := tests/*.c tests/*.h

all: install s21_calc.a tests

build:
	mkdir build
	cd ./build/ && cmake ../ && make && mv calc_2.app s21_calc.app

install: build
	@mkdir $(HOME)/Desktop/SmartCalc_v1.0/
	@cp -rf $(APP) $(HOME)/Desktop/SmartCalc_v1.0/
	make clean

uninstall:
	@rm -rf $(HOME)/Desktop/SmartCalc_v1.0/

dvi:
	open readme.md

leaks: test
	@CK_FORK=no leaks --atExit -- ./test.a

clang:
	clang-format -style=Google -n headers/*.h source/*.c source/*.cpp tests/*.c tests/*.h; 

dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	cp Makefile source/*.c headers/*.h CMakeLists.txt source/*.cpp ui/*.ui *.user Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	mv Archive_SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf Archive_SmartCalc_v1.0/

s21_calc.a:
	$(CC) $(CFLAG) -c $(BACKEND_FILES)
	@ar rcs s21_calc.a $(BACKEND_FILES_O)

test: $(TESTS)
	$(CC) $(CFLAGS)  $(LIBS) source/c_libs.c $(TESTS) -o test.a
	./test.a

gcov_report:
	$(CC) --coverage tests/*.c tests/*.h  -o s21_test -lcheck $(BACKEND_FILES)
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

clean:
	rm -rf *.o *.a
	rm -rf *.gcda *.gcno *.info
	rm -rf s21_test report
	rm -rf s21_calc s21_test
	rm -rf ./build*