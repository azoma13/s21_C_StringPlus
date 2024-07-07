#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(strchr1) {
  char s[] = "Hello, world!";
  int ch = 'h';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr2) {
  char s[] = "Hello, world!";
  int ch = '\0';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr3) {
  char s[] = "Hello, world!";
  int ch = ',';
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST

START_TEST(strchr4) {
  char s[] = "Hello, world!";
  int ch = 33;
  ck_assert_pstr_eq(strchr(s, ch), s21_strchr(s, ch));
}
END_TEST