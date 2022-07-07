CC = gcc
CFLAGS = -Wall -Werror -Wextra -c -fprofile-arcs -ftest-coverage 

all:check_s21_string.o s21_string.o s21_sprintf.o s21_string.a test test_run gcov_report

gcov_report: test_run
	gcov -f s21_string.gcda
	gcov -f s21_sprintf.gcda
	lcov -t "test" -o test.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o report test.info  --rc lcov_branch_coverage=1

test_run: test
	./test.out

test: s21_string.a check_s21_string.o
	$(CC) --coverage -o test.out check_s21_string.o -lcheck -L. s21_string.a 

s21_string.a: s21_string.o s21_sprintf.o
	ar rc s21_string.a s21_string.o s21_sprintf.o
	ranlib s21_string.a
	cp s21_string.a libs21_string.a

s21_string.o: s21_string.c 
	$(CC) $(CFLAGS) s21_string.c -lcheck 

s21_sprintf.o: s21_sprintf.c
	$(CC) $(CFLAGS) s21_sprintf.c -lcheck 

check_s21_string.o: check_s21_string.c
	$(CC) -Wall -Werror -Wextra -c check_s21_string.c 

clean:
	rm -rf *.o *.gcno *.gcda *.info *.out *.a *.gcov report

rebuild: clean all