#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *str_1 = (unsigned char *)str;
  int flag = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (*str_1 == c) {
      flag = 1;
      break;
    }
    str_1++;
  }
  if (!flag) {
    str_1 = s21_NULL;
  }
  return str_1;
}