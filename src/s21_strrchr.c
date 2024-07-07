#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  if (!str) return s21_NULL;

  s21_size_t len = s21_strlen(str);
  const char *end = str + len;

  if (!c) return (char *)end;

  do {
    if (*--end == c) {
      return (char *)end;
    }
  } while (end != str);

  return s21_NULL;
}