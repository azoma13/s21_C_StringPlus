#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL) {
    return s21_NULL;
  }
  const char spaces[] = " \t";
  const char *chars = trim_chars;
  if (chars == s21_NULL || *chars == 0) {
    chars = spaces;
  }
  s21_size_t len_src = s21_strlen(src);
  int flag;
  char *p_start = (char *)src;
  char *p_end = (char *)src + len_src - 1;
  for (s21_size_t i = 0; i < len_src; i++) {
    int n = 0;
    flag = 0;
    while (*(chars + n) != '\0') {
      if (src[i] == *(chars + n)) {
        p_start++;
        flag = 1;
        break;
      }
      n++;
    }
    if (flag == 1)
      continue;
    else
      break;
  }
  for (int i = len_src - 1; i > 0; i--) {
    int n = 0;
    flag = 0;
    while (chars[n] != '\0') {
      if (src[i] == chars[n]) {
        p_end--;
        flag = 1;
        break;
      }
      n++;
    }
    if (flag == 1)
      continue;
    else
      break;
  }
  char *new_str = (char *)malloc(sizeof(*new_str) * (p_end - p_start + 2));
  if (new_str != s21_NULL) {
    int size_new_str = (int)(sizeof(*new_str) * (p_end - p_start + 2));
    for (int i = 0; i < size_new_str; i++) {
      new_str[i] = *(p_start + i);
    }
    new_str[size_new_str - 1] = '\0';
  }
  return new_str;
}
