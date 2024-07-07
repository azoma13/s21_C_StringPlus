#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memcmp) {
  ck_assert_int_ge(
      s21_memcmp("Happy", "Happy", 6) * memcmp("Happy", "Happy", 6), 0);
  ck_assert_int_ge(
      s21_memcmp("Great world", "A", 2) * memcmp("Great world", "A", 2), 0);
  ck_assert_int_ge(
      s21_memcmp("Great world", "Z", 2) * memcmp("Great world", "Z", 2), 0);
  ck_assert_int_ge(
      s21_memcmp("Great world", "\0", 0) * memcmp("Great world", "\0", 0), 0);
  ck_assert_int_ge(
      s21_memcmp("Great world", "\0", 2) * memcmp("Great world", "\0", 2), 0);
  ck_assert_int_ge(s21_memcmp(" ", " ", 2) * memcmp(" ", " ", 2), 0);
  ck_assert_int_ge(s21_memcmp("a\n\0", "\n", 2) * memcmp("a\n\0", "\n", 2), 0);
  ck_assert_int_ge(s21_memcmp(" \0", "\0", 2) * memcmp(" \0", "\0", 2), 0);
  ck_assert_int_ge(s21_memcmp(" \0", " ", 2) * memcmp(" \0", " ", 2), 0);
  ck_assert_int_ge(s21_memcmp("\0", " ", 1) * memcmp("\0", " ", 1), 0);
  ck_assert_int_ge(s21_memcmp("\0", "\0", 1) * memcmp("\0", "\0", 1), 0);
  ck_assert_int_ge(s21_memcmp("\0", "\n", 1) * memcmp("\0", "\n", 1), 0);
  ck_assert_int_ge(s21_memcmp("a\n\0", "\0", 2) * memcmp("a\n\0", "\0", 2), 0);
}
END_TEST
