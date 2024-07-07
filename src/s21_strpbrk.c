#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  if (!str1 || !str2) return s21_NULL;

  char char_presence[256] = {0};
  for (s21_size_t i = 0; str2[i] != '\0'; i++) {
    unsigned char uc = str2[i];
    char_presence[uc] = 1;
  }

  for (s21_size_t i = 0; str1[i] != '\0'; i++) {
    unsigned char uc = str1[i];
    if (char_presence[uc]) {
      return (char *)(str1 + i);
    }
  }

  return s21_NULL;
}