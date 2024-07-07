#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (((unsigned char *)str1)[i] == ((unsigned char *)str2)[i]) continue;
    if (((unsigned char *)str1)[i] > ((unsigned char *)str2)[i]) {
      res = 1;
      break;
    } else {
      res = -1;
      break;
    }
  }
  return res;
}