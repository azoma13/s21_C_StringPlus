#include <check.h>

#include "../s21_string.h"

START_TEST(test_strncat) {
  char buffer1[128];
  char buffer2[128];
  void *b1;
  void *b2;

  strcpy(buffer1, "taxi");
  strcpy(buffer2, "taxi");
  b1 = s21_strncat(buffer1, " account", 100);
  b2 = strncat(buffer2, " account", 100);
  ck_assert_ptr_eq(b1, buffer1);
  ck_assert_ptr_eq(b2, buffer2);
  ck_assert_str_eq(buffer1, buffer2);

  strcpy(buffer1, "taxi");
  strcpy(buffer2, "taxi");
  b1 = s21_strncat(buffer1, "\naccount", 4);
  b2 = strncat(buffer2, "\naccount", 4);
  ck_assert_ptr_eq(b1, buffer1);
  ck_assert_ptr_eq(b2, buffer2);
  ck_assert_str_eq(buffer1, buffer2);

  strcpy(buffer1, "");
  strcpy(buffer2, "");
  b1 = s21_strncat(buffer1, "", 1);
  b2 = strncat(buffer2, "", 1);
  ck_assert_ptr_eq(b1, buffer1);
  ck_assert_ptr_eq(b2, buffer2);
  ck_assert_str_eq(buffer1, buffer2);

  strcpy(buffer1, "");
  strcpy(buffer2, "");
  b1 = s21_strncat(buffer1, "\n", 2);
  b2 = strncat(buffer2, "\n", 2);
  ck_assert_ptr_eq(b1, buffer1);
  ck_assert_ptr_eq(b2, buffer2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST
