#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strstr) {
  char str[] = "Try to find something in this string";
  char exist[] = "something";
  char nonexist[] = "anything";

  ck_assert_str_eq(s21_strstr(str, exist), strstr(str, exist));
  ck_assert_ptr_null(s21_strstr(str, nonexist));
  ck_assert_ptr_null(s21_strstr(str, 0));
  ck_assert_ptr_null(s21_strstr(NULL, 0));
}
END_TEST
