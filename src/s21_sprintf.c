#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"

void append_string(char **strPtr, char *target, specifier spec) {
  s21_size_t length = s21_strlen(target);
  length = (spec.accuracy >= 0 && spec.accuracy < (int)length)
               ? (s21_size_t)spec.accuracy
               : length;

  if (spec.flags[1]) {
    s21_memcpy(*strPtr, target, length);
    *strPtr += length;
  }

  if (spec.width > (int)length) {
    for (int i = 0; i < spec.width - (int)length; i++) {
      *(*strPtr) = ' ';
      (*strPtr)++;
    }
  }

  if (!spec.flags[1]) {
    s21_memcpy(*strPtr, target, length);
    *strPtr += length;
  }
}

void append_num(char **strPtr, long double num, specifier spec) {
  if (spec.accuracy == 0 && num == 0) return;

  char buff[5000];
  char result[5000];
  char *res = result;
  int skip = 0;

  if (spec.type == 'p') {
    spec.type = 'x';
    spec.length = 'l';
    spec.flags[2] = 1;
    if (!num) {
      s21_memcpy(result, "(nil)", 6);
      spec.accuracy = (int)s21_strlen(result);

      append_string(strPtr, result, spec);
      return;
    }
  }

  if (s21_strchr("gG", spec.type)) {
    if (spec.accuracy == 0) spec.accuracy = 1;
    int exp = get_exp(num);

    if (spec.accuracy > exp && exp >= -4) {
      spec.type = 'f';
      spec.accuracy -= 1 + exp;
    } else {
      spec.type -= 2;
      spec.accuracy -= 1;
    }
  }

  if (spec.flags[2] && num != 0) {
    if (s21_strchr("oxX", spec.type)) *res++ = '0';
    if (s21_strchr("xX", spec.type)) *res++ = spec.type;
  }

  if (s21_strchr("diu", spec.type))
    intToString(buff, num, spec);
  else if (s21_strchr("o", spec.type))
    (spec.length == 'l')
        ? intToString(buff, (unsigned long)num, spec)
        : ((spec.length == 'h') ? intToString(buff, (unsigned short)num, spec)
                                : intToString(buff, (unsigned int)num, spec));
  else if (s21_strchr("xX", spec.type))
    (spec.length == 'l')
        ? intToString(buff, (unsigned long)num, spec)
        : ((spec.length == 'h') ? intToString(buff, (unsigned short)num, spec)
                                : intToString(buff, (unsigned int)num, spec));

  if (spec.type == 'f')
    (!spec.length) ? floatToString(buff, (double)num, spec)
                   : floatToString(buff, num, spec);

  if (s21_strchr("eE", spec.type)) {
    (!spec.length) ? floatToScientificString(buff, (double)num, spec.accuracy,
                                             spec.type, spec.flags[2])
                   : floatToScientificString(buff, num, spec.accuracy,
                                             spec.type, spec.flags[2]);
  }

  if (isnan(num) || isinf(num)) spec.accuracy = 0;

  s21_size_t length = s21_strlen(buff) + (spec.type == 'o' && spec.flags[2]);

  if ((spec.flags[0] || spec.flags[4]) && num >= 0 &&
      s21_strchr("difeE", spec.type)) {
    *res++ = (spec.flags[4]) ? ' ' : '+';
  }

  if (*buff == '-') {
    *res++ = '-';
    skip = 1;
    length--;
  }

  if (spec.accuracy - (int)length > 0) {
    for (int i = 0; i < spec.accuracy - (int)length; i++) {
      *res++ = '0';
    }
  }

  s21_memcpy(res, buff + skip, length + 1);

  spec.accuracy = (int)s21_strlen(result);

  append_string(strPtr, result, spec);
}

void append_char(char **strPtr, char ch, specifier spec) {
  if (spec.flags[1]) {
    *(*strPtr) = ch;
    (*strPtr)++;
  }

  for (int i = 0; i < spec.width - 1; i++) {
    *(*strPtr) = ' ';
    (*strPtr)++;
  }

  if (!spec.flags[1]) {
    *(*strPtr) = ch;
    (*strPtr)++;
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *t = str;
  char *p = (char *)format;
  specifier spec;

  while (*p) {
    if (*p == '%') {
      if (*(p + 1) == '%') {
        *t++ = '%';
        p += 2;
        continue;
      }
      parse_format(p, &p, &spec);

      if (spec.width == -2) {
        int width = va_arg(args, int);
        spec.width = (width >= 0) ? width : 0;
      }

      if (spec.accuracy == -2) {
        int accuracy = va_arg(args, int);
        spec.accuracy = (accuracy >= 0) ? accuracy : 0;
      }

      if (s21_strchr("diouxX", spec.type)) {
        if (spec.length == 'l')
          (spec.type == 'u')
              ? append_num(&t, (unsigned long)va_arg(args, long), spec)
              : append_num(&t, va_arg(args, long), spec);
        else if (spec.length == 'h')
          (spec.type == 'u')
              ? append_num(&t, (unsigned short)va_arg(args, int), spec)
              : append_num(&t, (short)va_arg(args, int), spec);
        else
          (spec.type == 'u')
              ? append_num(&t, (unsigned int)va_arg(args, int), spec)
              : append_num(&t, va_arg(args, int), spec);
      } else if (s21_strchr("feEgG", spec.type)) {
        if (spec.length == 'L')
          append_num(&t, va_arg(args, long double), spec);
        else
          append_num(&t, va_arg(args, double), spec);
      } else if (spec.type == 'c')
        append_char(&t, va_arg(args, int), spec);
      else if (spec.type == 's')
        append_string(&t, va_arg(args, char *), spec);
      else if (spec.type == 'p')
        append_num(&t, va_arg(args, long), spec);
      else if (spec.type == 'n')
        *(va_arg(args, int *)) = t - str;
      else if (spec.type == '%')
        *t++ = '%';
    } else {
      *t++ = *p++;
    }
  }

  va_end(args);
  *t++ = '\0';
  return t - str - 1;
}