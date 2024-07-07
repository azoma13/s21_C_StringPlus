#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t n = s21_strlen(src) + s21_strlen(str);
  unsigned char *s = malloc(sizeof(*s) * (n + 1));
  if (!s) {
    s = s21_NULL;
  } else {
    int k = 0;
    for (s21_size_t i = 0; i < n + 1; i++) {
      if (start_index == i) {
        for (s21_size_t j = 0; j < s21_strlen(str); j++) {
          s[i] = str[j];
          i++;
        }
        i--;
      } else {
        s[i] = src[k];
        k++;
      }
    }
    s[n] = '\0';
  }
  return (void *)s;
}
