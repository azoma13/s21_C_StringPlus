#include <check.h>

#include "../s21_string.h"

START_TEST(test_strncpy) {
  char buffer1[16];
  char buffer2[16];
  void *b1;
  void *b2;

  memset(buffer1, '\0', 16);
  memset(buffer2, '\0', 16);
  b1 = s21_strncpy(buffer1, "region", 7);
  b2 = strncpy(buffer2, "region", 7);
  ck_assert_ptr_eq(b1, buffer1);
  ck_assert_ptr_eq(b2, buffer2);
  ck_assert_str_eq(buffer1, buffer2);

  memset(buffer1, '\0', 16);
  memset(buffer2, '\0', 16);
  b1 = s21_strncpy(buffer1, "", 1);
  b2 = strncpy(buffer2, "", 1);
  ck_assert_ptr_eq(b1, buffer1);
  ck_assert_ptr_eq(b2, buffer2);
  ck_assert_str_eq(buffer1, buffer2);

  memset(buffer1, '\0', 16);
  memset(buffer2, '\0', 16);
  b1 = s21_strncpy(buffer1, "\n", 2);
  b2 = strncpy(buffer2, "\n", 2);
  ck_assert_ptr_eq(b1, buffer1);
  ck_assert_ptr_eq(b2, buffer2);
  ck_assert_str_eq(buffer1, buffer2);

  memset(buffer1, '\0', 16);
  memset(buffer2, '\0', 16);
  b1 = s21_strncpy(buffer1, "\0\n", 3);
  b2 = strncpy(buffer2, "\0\n", 3);
  ck_assert_ptr_eq(b1, buffer1);
  ck_assert_ptr_eq(b2, buffer2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST
