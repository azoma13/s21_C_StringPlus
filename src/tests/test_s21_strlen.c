#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(strlen1) {
  char str[] = "Hello, world!";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen2) {
  char str[] = "\0";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen3) {
  char str[] = "";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen4) {
  char str[] = "\n test \n test";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen5) {
  char str[] = "\t test \t test";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen6) {
  char str[] = "\0 test \0 test";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen7) {
  char str[] = "Hello, world! \0 Hello, world!";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST