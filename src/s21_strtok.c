#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last = s21_NULL;
  if (str) last = str;
  if (last == s21_NULL || *last == '\0') return s21_NULL;
  char *c = last;

  while (*c && s21_strchr(delim, *c)) c++;
  if (*c == '\0') {
    last = s21_NULL;
    return s21_NULL;
  }

  char *start = c;

  while (*c && !s21_strchr(delim, *c)) c++;
  if (*c == '\0') {
    last = c;
  } else {
    *c = '\0';
    last = c + 1;
  }

  return start;
}
