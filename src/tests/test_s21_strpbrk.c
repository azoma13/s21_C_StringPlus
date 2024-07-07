#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strpbrk) {
  char str[] = "Try to find something in this string";
  char exist[] = "ifd";
  char nonexist[] = "alk";

  ck_assert_str_eq(s21_strpbrk(str, exist), strpbrk(str, exist));
  ck_assert_ptr_null(s21_strpbrk(str, nonexist));
  ck_assert_ptr_null(s21_strpbrk(str, 0));
  ck_assert_ptr_null(s21_strpbrk(NULL, 0));
}
END_TEST
