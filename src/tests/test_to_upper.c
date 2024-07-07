#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

START_TEST(test_to_upper) {
  char str1[128];
  char answ[128];
  char *tok1;
  char *tok2;

  strcpy(str1, "123 TeSt\n StRiNg");
  strcpy(answ, "123 TEST\n STRING");
  tok1 = s21_to_upper(str1);
  tok2 = answ;
  ck_assert_str_eq(tok1, tok2);
  free(tok1);
}
END_TEST
