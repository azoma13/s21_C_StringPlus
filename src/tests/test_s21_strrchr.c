#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strrchr) {
  char str[] = "Try to find something in this string";
  char exist = 'y';
  char nonexist = 'w';

  ck_assert_str_eq(s21_strrchr(str, exist), strrchr(str, exist));
  ck_assert_ptr_null(s21_strrchr(str, nonexist));
  ck_assert_str_eq(s21_strrchr(str, 0), strrchr(str, 0));
  ck_assert_ptr_null(s21_strrchr(NULL, 0));
}
END_TEST
