#include <stdlib.h>

#include "s21_string.h"

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }
  int n = s21_strlen(str);
  unsigned char *p = malloc(sizeof(*p) * (n + 1));
  if (!p) {
    p = s21_NULL;
  } else {
    for (int i = 0; i < (n + 1); i++) {
      if (*str >= 'A' && *str <= 'Z') {
        *p = *str + 32;
      } else {
        *p = *str;
      }
      p++;
      str++;
    }
    p = p - n - 1;
  }
  return (void *)p;
}
