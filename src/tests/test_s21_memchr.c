#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(memchr1) {
  char str[] = "Hello, world!";
  int ch = ' ';
  size_t len = strlen(str);
  ck_assert_ptr_eq(s21_memchr(str, ch, len), memchr(str, ch, len));
}
END_TEST

START_TEST(memchr2) {
  char str[] = "Hello, world!";
  int ch = 101;
  size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr3) {
  char str[] = "Hello, world!";
  int ch = '1';
  size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), s21_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr4) {
  char str[] = "Hello, world!";
  int ch = 'l';
  size_t len = 10;
  ck_assert_ptr_eq(s21_memchr(str, ch, len), memchr(str, ch, len));
}
END_TEST