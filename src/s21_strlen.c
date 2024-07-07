#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  unsigned char *str1 = (unsigned char *)str;
  s21_size_t result = 0;
  while (*str1 != '\0') {
    result++;
    str1++;
  }
  return result;
}
