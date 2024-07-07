#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strtok) {
  char str[] = "Test 1|Test 2,Test 3.Test 4";
  char delim[] = ".|,";

  char *token_s21 = s21_strtok(str, delim);
  char *token_def = strtok(str, delim);

  while (token_s21 != NULL && token_def != NULL) {
    ck_assert_str_eq(token_s21, token_def);
    token_s21 = s21_strtok(NULL, delim);
    token_def = strtok(NULL, delim);
  }

  char str1[] = " ,";
  token_s21 = s21_strtok(str1, " ,");
  token_def = strtok(str1, " ,");
  ck_assert_ptr_null(token_s21);

  char str2[] = "test,";
  token_s21 = s21_strtok(str2, ",");
  token_def = strtok(str2, ",");
  ck_assert_str_eq(token_s21, token_def);

  ck_assert_ptr_null(s21_strtok(NULL, ","));

  char str3[] = "test";
  ck_assert_str_eq(s21_strtok(str3, ","), strtok(str3, ","));
}
END_TEST