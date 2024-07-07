#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t buff = s21_strlen(str1);
  unsigned char *str2_1 = (unsigned char *)str2;
  for (s21_size_t i = 0; i < s21_strlen(str2); i++) {
    unsigned char *str1_1 = (unsigned char *)str1;
    for (s21_size_t j = 0; j < s21_strlen(str1); j++) {
      if (*str1_1 == *str2_1) {
        if (j < buff) {
          buff = j;
        }
      }
      str1_1++;
    }
    str2_1++;
  }
  return buff;
}