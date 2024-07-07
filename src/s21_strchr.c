#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *str1 = (char *)str;
  int c1 = (int)c;
  while (*str1 != '\0') {
    if (*str1 == c1) {
      break;
    }
    str1++;
  }
  if (*str1 == '\0' && c1 != '\0') {
    str1 = s21_NULL;
  }
  return str1;
}