#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

START_TEST(test_insert) {
  char str1[128];
  char answ[128];
  char *tok1;
  char *tok2;

  strcpy(str1, "123 TeSt StRiNg");
  strcpy(answ, "123 TeSt SHitRiNg");
  tok1 = s21_insert(str1, "Hi", 10);
  tok2 = answ;
  ck_assert_str_eq(tok1, tok2);
  free(tok1);

  strcpy(str1, "123 TeSt StRiNg");
  strcpy(answ, "Hi123 TeSt StRiNg");
  tok1 = s21_insert(str1, "Hi", 0);
  tok2 = answ;
  ck_assert_str_eq(tok1, tok2);
  free(tok1);
}
END_TEST
