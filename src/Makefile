CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LIBS = -lcheck -lm -lpthread -lrt -lsubunit

S21_SRC = s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memset.c s21_strcspn.c s21_strchr.c s21_strerror.c s21_strlen.c s21_strncmp.c s21_strncat.c s21_strncpy.c s21_strpbrk.c s21_strrchr.c s21_strstr.c s21_strtok.c common.c s21_sprintf.c s21_sscanf.c s21_insert.c s21_to_upper.c s21_to_lower.c s21_trim.c
S21_OBJ = $(S21_SRC:.c=.o)
S21_LIB = s21_string.a

all: gcov_report

gcov_report: gcov_string_lib test
	gcov $(S21_SRC)
	lcov --capture --directory . --output-file coverage.info --no-external
	lcov --remove coverage.info '*common.c' --output-file coverage.info
	lcov --remove coverage.info 'test*' --output-file coverage.info
	genhtml coverage.info --output-directory coverage_html
	open coverage_html/index.html

gcov_string_lib: $(S21_SRC)
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c $^ $(LIBS) -lgcov
	ar rcs $(S21_LIB) $(S21_OBJ)

test: test.c $(S21_LIB)
	$(CC) $(CFLAGS) -fprofile-arcs $^ $(LIBS) $(S21_LIB) -L. -o test
	./test
	

$(S21_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(S21_LIB): $(S21_OBJ)
	ar rcs $@ $(S21_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.a *.gcda *.gcno *.gcov coverage.info test
	rm -rf coverage_html/

rebuild: clean all

.PHONY: all clean