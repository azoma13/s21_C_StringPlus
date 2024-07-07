#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "s21_string.h"

int skip_char(char **str, specifier spec) {
  if (spec.width != -2 && spec.width <= 0) return 0;
  int counter = spec.width;
  while (counter == -2 || counter > 0) {
    (*str)++;
    counter--;
  }
  return 1;
}

int skip_int(char **str, specifier spec) {
  if (spec.width != -2 && spec.width <= 0) return 0;
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r') {
    (*str)++;
  }
  int counter = spec.width;
  int minusCounter = 0;
  while (
      ((**str >= '0' && **str <= '9') || (**str == '-' && minusCounter < 1)) &&
      (counter <= -2 || counter > 0)) {
    if (**str == '-') minusCounter++;
    (*str)++;
    counter--;
  }
  return 1;
}

int skip_float(char **str, specifier spec) {
  if (spec.width != -2 && spec.width <= 0) return 0;
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r') {
    (*str)++;
  }
  int counter = spec.width;
  int dotCounter = 0;
  int minusCounter = 0;
  while (((**str >= '0' && **str <= '9') ||
          (**str == '-' && minusCounter < 1) ||
          (**str == '.' && dotCounter < 1)) &&
         (counter <= -2 || counter > 0)) {
    if (**str == '.') dotCounter++;
    if (**str == '-') minusCounter++;
    (*str)++;
    counter--;
  }
  return 1;
}

int skip_str(char **str, specifier spec) {
  if (spec.width != -2 && spec.width <= 0) return 0;
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r') {
    (*str)++;
  }
  int count = 0;
  while (**str != ' ' && **str != '\n' && **str != '\t' && **str != '\r' &&
         (spec.width == -2 || count < spec.width)) {
    if (**str == '\0' && (count < spec.width || spec.width == -1)) return -1;
    (*str)++;
    count++;
  }
  return 1;
}

int skip_pointer(char **str, specifier spec) {
  if (spec.width != -2 && spec.width <= 0) return 0;
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r') {
    (*str)++;
  }
  int counter = spec.width;
  int leadingZero = **str == '0';
  while (((**str >= '0' && **str <= '9') || (**str >= 'A' && **str <= 'F') ||
          (**str >= 'a' && **str <= 'f') ||
          (**str == 'x' && leadingZero == 1)) &&
         (counter <= -2 || counter > 0)) {
    if (**str == 'x') leadingZero = 0;
    (*str)++;
    counter--;
  }
  return 1;
}

int assign_char(char **str, specifier spec, va_list args) {
  int result = 0;
  if (**str) {
    char *target = va_arg(args, char *);
    *target = *(*str)++;
    result = 1;
  }
  if (spec.width-- > 0) result *= skip_char(str, spec);
  return result;
}

int assign_int(char **str, specifier spec, va_list args) {
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r') {
    (*str)++;
  }
  if (spec.width != -1 && spec.width <= 0) return 0;

  char temp_str[512];
  int count = 0;
  while ((spec.width == -1 || count < spec.width) &&
         ((**str >= '0' && **str <= '9') || **str == '-' || **str == '+' ||
          **str == 'x' || **str == 'X' || (**str >= 'a' && **str <= 'f') ||
          (**str >= 'A' && **str <= 'F'))) {
    temp_str[count++] = *(*str)++;
  }
  if (count == 0) return 0;
  temp_str[count] = '\0';

  char *end_ptr;
  long value;

  switch (spec.type) {
    case 'd':
      value = s21_strtol(temp_str, &end_ptr, 10);
      break;
    case 'i':
      value = s21_strtol(temp_str, &end_ptr, 0);
      break;
    case 'u':
      value = (unsigned long)s21_strtol(temp_str, &end_ptr, 10);
      break;
    case 'o':
      value = s21_strtol(temp_str, &end_ptr, 8);
      break;
    case 'x':
    case 'X':
      value = s21_strtol(temp_str, &end_ptr, 16);
      break;
  }

  if (end_ptr == temp_str) return 0;

  if (spec.length == 'h') {
    short *target = va_arg(args, short *);
    *target = (short)value;
  } else if (spec.length == 'l') {
    long *target = va_arg(args, long *);
    *target = (long)value;
  } else {
    int *target = va_arg(args, int *);
    *target = (int)value;
  }

  return 1;
}

int assign_float(char **str, specifier spec, va_list args) {
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r') {
    (*str)++;
  }
  if (spec.width != -1 && spec.width <= 0) return 0;

  char temp_str[512];
  int count = 0;

  while ((spec.width == -1 || count < spec.width) &&
         ((**str >= '0' && **str <= '9') || **str == '-' || **str == '+' ||
          **str == '.' || (**str == 'e' || **str == 'E'))) {
    temp_str[count++] = *(*str)++;
  }
  if (count == 0) return 0;
  temp_str[count] = '\0';

  char *end_ptr;
  long double value = s21_strtod(temp_str, &end_ptr);

  if (end_ptr == temp_str) return 0;

  if (spec.length == 'L') {
    long double *target = va_arg(args, long double *);
    *target = (long double)value;
  } else if (spec.length == 'l') {
    double *target = va_arg(args, double *);
    *target = (double)value;
  } else {
    float *target = va_arg(args, float *);
    *target = (float)value;
  }
  return 1;
}

int assign_str(char **str, specifier spec, va_list args) {
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r') {
    (*str)++;
  }
  if (!str) return 0;
  char *target = va_arg(args, char *);
  int count = 0;
  while ((spec.width == -1 || count < spec.width) && **str != ' ' &&
         **str != '\n' && **str != '\t' && **str != '\r') {
    if (**str == '\0' && (count < spec.width || spec.width == -1)) return -1;
    *target++ = **str;
    count++;
    (*str)++;
  }
  *target = '\0';
  return 1;
}

int assign_pointer(char **str, specifier spec, va_list args) {
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r') {
    (*str)++;
  }

  if (spec.width == 1 || spec.width == 2) {
    if (**str == '0' && (spec.width == 2 && *(*str + 1) == 'x')) {
      (*str)++;
      (*str)++;
    }
    void **target = va_arg(args, void **);
    *target = NULL;
    return 1;
  }

  char temp_str[512];
  int count = 0;

  if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
    temp_str[count++] = *(*str)++;
    temp_str[count++] = *(*str)++;
  }

  while ((**str >= '0' && **str <= '9') || (**str >= 'a' && **str <= 'f') ||
         (**str >= 'A' && **str <= 'F')) {
    temp_str[count++] = *(*str)++;
    if (count >= (int)sizeof(temp_str) - 1) break;
  }
  temp_str[count] = '\0';

  char *end_ptr;
  long addr = strtol(temp_str, &end_ptr, 16);

  if (end_ptr == temp_str) return 0;

  void **target = va_arg(args, void **);
  *target = (void *)addr;

  return 1;
}

int process_format(char **str, specifier spec, va_list args) {
  int result = 0;
  switch (spec.type) {
    case 'c':
      if (!spec.skip)
        result = assign_char(str, spec, args);
      else
        result = skip_char(str, spec);
      break;
    case 'd':
    case 'i':
    case 'o':
    case 'u':
    case 'x':
    case 'X':
      if (!spec.skip)
        result = assign_int(str, spec, args);
      else {
        result = skip_int(str, spec);
      }
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      if (!spec.skip)
        result = assign_float(str, spec, args);
      else
        result = skip_float(str, spec);
      break;
    case 's':
      if (!spec.skip)
        result = assign_str(str, spec, args);
      else
        result = skip_str(str, spec);
      break;
    case 'p':
      if (!spec.skip)
        result = assign_pointer(str, spec, args);
      else
        result = skip_pointer(str, spec);
      break;
    default:
      return -1;
      break;
  }
  return result;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *t = (char *)str;
  char *p = (char *)format;
  specifier spec;

  int arguments_processed = 0;

  while (*p) {
    if (*p != '%' && *p != *t) {
      if (*p == ' ' || *p == '\n' || *p == '\t' || *p == '\r') {
        p++;
      } else {
        va_end(args);
        return -1;
      }
    }
    if (*p == '%') {
      if (*(p + 1) == '%') {
        p += 2;
        if (*t++ == '%')
          continue;
        else
          break;
      }
      parse_format(p, &p, &spec);
      if (spec.width == -2 && !spec.skip) spec.skip = 1;
      if (spec.type == 'n') {
        *(va_arg(args, int *)) = t - str;
        continue;
      }
      int result = process_format(&t, spec, args) * (!spec.skip);
      if (result == 0 && !spec.skip)
        break;
      else if (result == -1)
        return -1;
      else
        arguments_processed += result;
    } else if (*p == *t) {
      t++;
      p++;
    }
  }
  return arguments_processed;
}