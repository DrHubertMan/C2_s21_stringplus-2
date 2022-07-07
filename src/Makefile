CC = gcc
CFLAGSCOV = -Wall -Werror -Wextra -c -fprofile-arcs -ftest-coverage -lcheck
CFLAGS = -Wall -Werror -Wextra -c

all:check_s21_string.o s21_sprintf_test.o s21_string_test.o s21_string_test.a test gcov_report s21_string.a test_ff

gcov_report: test
	gcov -f s21_string_test.gcda
	gcov -f s21_sprintf_test.gcda
	lcov -t "test" -o test.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o report test.info  --rc lcov_branch_coverage=1

test:check_s21_string.o  s21_string_test.a 
	$(CC) --coverage -o test_coverage.out check_s21_string.o -lcheck -L. s21_string_test.a
	./test_coverage.out

s21_string_test.a: s21_string_test.o s21_sprintf_test.o
	ar rc s21_string_test.a s21_string_test.o s21_sprintf_test.o
	ranlib s21_string_test.a

s21_string_test.o:
	$(CC) $(CFLAGSCOV) -o s21_string_test.o s21_string.c

s21_sprintf_test.o:
	$(CC) $(CFLAGSCOV) -o s21_sprintf_test.o s21_sprintf.c 

check_s21_string.o:
	$(CC) $(CFLAGS) check_s21_string.c

test_ff: s21_string.a check_s21_string.o
	$(CC) -o test.out check_s21_string.o -L. s21_string.a -lcheck -lm -lpthread
	./test.out

s21_string.a: s21_string.o s21_sprintf.o
	ar rc s21_string.a s21_string.o s21_sprintf.o
	ranlib s21_string.a

s21_string.o:
	$(CC) $(CFLAGS) s21_string.c

s21_sprintf.o:
	$(CC) $(CFLAGS) s21_sprintf.c

clean:
	rm -rf *.o *.gcno *.gcda *.info *.out *.a *.gcov report

rebuild: clean all