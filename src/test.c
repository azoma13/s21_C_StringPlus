#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "s21_string.h"
#include "tests/test_insert.c"
#include "tests/test_memcmp.c"
#include "tests/test_memcpy.c"
#include "tests/test_s21_memchr.c"
#include "tests/test_s21_memset.c"
#include "tests/test_s21_sprintf.c"
#include "tests/test_s21_sscanf.c"
#include "tests/test_s21_strchr.c"
#include "tests/test_s21_strcspn.c"
#include "tests/test_s21_strerror.c"
#include "tests/test_s21_strlen.c"
#include "tests/test_s21_strpbrk.c"
#include "tests/test_s21_strrchr.c"
#include "tests/test_s21_strstr.c"
#include "tests/test_s21_strtok.c"
#include "tests/test_strncat.c"
#include "tests/test_strncmp.c"
#include "tests/test_strncpy.c"
#include "tests/test_to_lower.c"
#include "tests/test_to_upper.c"
#include "tests/test_trim.c"

int main() {
  int number_failed;

  Suite *s;
  SRunner *sr;

  s = suite_create("s21_string test");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sprintf);
  tcase_add_test(tc_core, test_s21_sscanf);
  tcase_add_test(tc_core, test_s21_strerror);
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_strtok);
  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strncmp);
  tcase_add_test(tc_core, test_strncpy);
  tcase_add_test(tc_core, test_insert);
  tcase_add_test(tc_core, test_to_lower);
  tcase_add_test(tc_core, test_to_upper);
  tcase_add_test(tc_core, test_trim);
  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_memcpy);
  tcase_add_test(tc_core, memchr1);
  tcase_add_test(tc_core, memchr2);
  tcase_add_test(tc_core, memchr3);
  tcase_add_test(tc_core, memchr4);
  tcase_add_test(tc_core, memset1);
  tcase_add_test(tc_core, memset2);
  tcase_add_test(tc_core, memset3);
  tcase_add_test(tc_core, memset4);
  tcase_add_test(tc_core, strchr1);
  tcase_add_test(tc_core, strchr2);
  tcase_add_test(tc_core, strchr3);
  tcase_add_test(tc_core, strchr4);
  tcase_add_test(tc_core, strcspn1);
  tcase_add_test(tc_core, strcspn2);
  tcase_add_test(tc_core, strcspn3);
  tcase_add_test(tc_core, strcspn4);
  tcase_add_test(tc_core, strlen1);
  tcase_add_test(tc_core, strlen2);
  tcase_add_test(tc_core, strlen3);
  tcase_add_test(tc_core, strlen4);
  tcase_add_test(tc_core, strlen5);
  tcase_add_test(tc_core, strlen6);
  tcase_add_test(tc_core, strlen7);

  suite_add_tcase(s, tc_core);
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : -1;
}