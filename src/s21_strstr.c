#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (!haystack || !needle) return s21_NULL;

  s21_size_t haystack_len = s21_strlen(haystack);
  s21_size_t needle_len = s21_strlen(needle);

  if (needle_len == 0) return (char *)haystack;

  if (haystack_len < needle_len) return s21_NULL;

  for (s21_size_t i = 0; i <= haystack_len - needle_len; i++) {
    if (s21_strncmp(haystack + i, needle, needle_len) == 0)
      return (char *)(haystack + i);
  }
  return s21_NULL;
}