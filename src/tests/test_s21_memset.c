#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(memset1) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  int ch = ' ';
  size_t n = strlen(s1);
  ck_assert_str_eq(memset(s1, ch, n), s21_memset(s2, ch, n));
}
END_TEST

START_TEST(memset2) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  int ch = ' ';
  size_t n = 5;
  ck_assert_str_eq(memset(s1, ch, n), s21_memset(s2, ch, n));
}
END_TEST

START_TEST(memset3) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  int ch = ' ';
  size_t n = 0;
  ck_assert_str_eq(memset(s1, ch, n), s21_memset(s2, ch, n));
}
END_TEST

START_TEST(memset4) {
  char s1[] = "";
  char s2[] = "";
  int ch = '\0';
  size_t n = 0;
  ck_assert_str_eq(memset(s1, ch, n), s21_memset(s2, ch, n));
}
END_TEST