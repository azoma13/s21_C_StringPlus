#include <check.h>

#include "../s21_string.h"

START_TEST(test_strncmp) {
  ck_assert_int_ge(
      s21_strncmp("Happy", "Happy", 10) * strncmp("Happy", "Happy", 10), 0);
  ck_assert_int_ge(
      s21_strncmp("Great world", "A", 3) * strncmp("Great world", "A", 3), 0);
  ck_assert_int_ge(
      s21_strncmp("Great world", "Z", 2) * strncmp("Great world", "Z", 2), 0);
  ck_assert_int_ge(
      s21_strncmp("Great world", "\0", 0) * strncmp("Great world", "\0", 0), 0);
  ck_assert_int_ge(
      s21_strncmp("Great world", "\0", 20) * strncmp("Great world", "\0", 20),
      0);
  ck_assert_int_ge(s21_strncmp("a\n\0", "\0", 3) * strncmp("a\n\0", "\0", 3),
                   0);
  ck_assert_int_ge(s21_strncmp("a\n\0", "\n", 3) * strncmp("a\n\0", "\n", 3),
                   0);
  ck_assert_int_ge(s21_strncmp("\0", "\0", 1) * strncmp("\0", "\0", 1), 0);
  ck_assert_int_ge(s21_strncmp("\0", "\n", 1) * strncmp("\0", "\n", 1), 0);
  ck_assert_int_ge(s21_strncmp(" \0", "\0", 2) * strncmp(" \0", "\0", 2), 0);
  ck_assert_int_ge(s21_strncmp(" \0", " ", 2) * strncmp(" \0", " ", 2), 0);
  ck_assert_int_ge(s21_strncmp(" ", " ", 15) * strncmp(" ", " ", 15), 0);
  ck_assert_int_ge(s21_strncmp("\0", " ", 1) * strncmp("\0", " ", 1), 0);

  ck_assert_int_ge(s21_strncmp("\0", "\0", 20) * strncmp("\0", "\0", 20), 0);
  ck_assert_int_ge(s21_strncmp("\0", "\n", 20) * strncmp("\0", "\n", 20), 0);
  ck_assert_int_ge(s21_strncmp(" \0", " ", 20) * strncmp(" \0", " ", 20), 0);
  ck_assert_int_ge(s21_strncmp(" ", " ", 20) * strncmp(" ", " ", 20), 0);
  ck_assert_int_ge(s21_strncmp("\0", " ", 20) * strncmp("\0", " ", 20), 0);
}
END_TEST
