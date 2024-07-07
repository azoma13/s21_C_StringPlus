#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strerror) {
  for (int i = -10; i < 150; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST