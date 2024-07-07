#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "s21_string.h"

void reverse_string(char *start, int length) {
  int i = 0;
  int j = length - 1;
  while (i < j) {
    char temp = start[i];
    start[i] = start[j];
    start[j] = temp;
    i++;
    j--;
  }
}

void intToString(char *buffer, long int number, specifier spec) {
  int i = 0;
  int isNegative = 0;
  int base;
  if (s21_strchr("diu", spec.type))
    base = 10;
  else if (s21_strchr("xX", spec.type))
    base = 16;
  else
    base = 8;

  if (number < 0 && base == 10) {
    isNegative = 1;
    number = -number;
  }

  do {
    int digit = number % base;
    buffer[i++] = (digit > 9) ? (digit - 10) + 'a' : digit + '0';
    number /= base;
  } while (number != 0);

  if (isNegative) {
    buffer[i++] = '-';
  }

  if (spec.flags[3] && i < spec.width) {
    while (i < spec.width -
                   2 * (s21_strchr("xX", spec.type) != NULL && spec.flags[2]) -
                   1 * (spec.type == 'o' && spec.flags[2])) {
      buffer[i++] = '0';
    }
  }

  buffer[i] = '\0';

  reverse_string(buffer, i);
}

void floatToString(char *buffer, long double value, specifier spec) {
  if (isnan(value)) {
    s21_memcpy(buffer, "nan", 4);
    return;
  }

  if (isinf(value) && value > 0) {
    s21_memcpy(buffer, "inf", 4);
    return;
  }

  if (isinf(value) && value < 0) {
    s21_memcpy(buffer, "-inf", 5);
    return;
  }

  long long roundedValue =
      (long long)(value * pow(10, spec.accuracy) + (value < 0 ? -0.5 : 0.5));
  int isNegative = value < 0;
  if (isNegative) {
    roundedValue = -roundedValue;
  }

  int i = 0;
  int fractionalPartCount = spec.accuracy;
  while (spec.accuracy-- > 0) {
    buffer[i++] = '0' + roundedValue % 10;
    roundedValue /= 10;
  }

  if (fractionalPartCount > 0 || spec.flags[2]) {
    buffer[i++] = '.';
  }

  if (roundedValue == 0) {
    buffer[i++] = '0';
  } else {
    while (roundedValue > 0) {
      buffer[i++] = '0' + roundedValue % 10;
      roundedValue /= 10;
    }
  }

  if (spec.flags[3] && i < spec.width) {
    while (i < spec.width - (spec.flags[2] && !s21_strchr(buffer, '.')) -
                   (isNegative || spec.flags[0])) {
      buffer[i++] = '0';
    }
  }

  if (isNegative) {
    buffer[i++] = '-';
  }

  reverse_string(buffer, i);
  buffer[i] = '\0';
}

int get_exp(long double value) {
  int exp = 0;

  while (value > 10 || value < -10) {
    value /= 10;
    exp++;
  }

  while (value < 1 && value > -1) {
    value *= 10;
    exp--;
  }

  return exp;
}

long long get_mantissa(long double value, int precision) {
  long long limit = pow(10, precision + 1);
  while ((value < limit / 10) && (value > -limit / 10)) value *= 10;
  while ((value > limit) || (value < -limit)) value /= 10;
  return round(value);
}

void floatToScientificString(char *buffer, long double value, int precision,
                             char ch, int point) {
  int exp = get_exp(value);
  long long mantissa = get_mantissa(value, precision);
  int isNegative = value < 0;
  int expNegative = exp < 0;

  int i = 0;

  if (isNegative) mantissa = -mantissa;
  if (expNegative) exp = -exp;

  if (exp < 10) {
    buffer[i++] = '0' + exp;
    buffer[i++] = '0';
  } else {
    while (exp > 0) {
      buffer[i++] = '0' + (int)(exp % 10);
      exp /= 10;
    }
  }

  if (expNegative)
    buffer[i++] = '-';
  else
    buffer[i++] = '+';

  buffer[i++] = ch;
  if (point && precision == 0) buffer[i++] = '.';

  while (mantissa > 0) {
    buffer[i++] = '0' + (int)(mantissa % 10);
    mantissa /= 10;
    if (mantissa > 0 && mantissa < 10) buffer[i++] = '.';
  }
  if (isNegative) buffer[i++] = '-';
  reverse_string(buffer, i);
  buffer[i++] = '\0';
}

long int s21_strtol(const char *str, char **endptr, int base) {
  long int result = 0;
  int sign = 1;

  if (str == NULL || base < 0 || base == 1 || base > 36) {
    if (endptr) *endptr = (char *)str;
    return 0;
  }

  while (isspace((unsigned char)*str)) str++;

  if (*str == '-' || *str == '+') {
    sign = (*str == '-') ? -1 : 1;
    str++;
  }

  if (base == 0) {
    if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
      base = 16;
      str += 2;
    } else if (*str == '0') {
      base = 8;
      str++;
    } else {
      base = 10;
    }
  } else if (base == 16) {
    if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
      str += 2;
    }
  }

  while (*str) {
    int digit = 0;

    if ((*str >= '0' && *str <= '9' && base >= 10) ||
        (*str >= '0' && *str <= '7' && base == 8)) {
      digit = *str - '0';
    } else if (*str >= 'A' && *str <= 'Z' && base == 16) {
      digit = *str - 'A' + 10;
    } else if (*str >= 'a' && *str <= 'z' && base == 16) {
      digit = *str - 'a' + 10;
    } else {
      break;
    }

    if (digit >= base) break;

    if (result > LONG_MAX / base ||
        (result == LONG_MAX / base && digit > LONG_MAX % base)) {
      errno = ERANGE;
      result = sign == 1 ? LONG_MAX : LONG_MIN;
      break;
    }

    result = result * base + digit;
    str++;
  }

  if (endptr) *endptr = (char *)str;
  return result * sign;
}

double pointstrtof(const char *str, char **endptr) {
  double result = 0.0f;
  double sign = 1.0f;
  double fraction = 0.1f;
  int state = 0;

  while (isspace(*str)) {
    str++;
  }

  if (*str == '-' || *str == '+') {
    sign = (*str == '-') ? -1.0f : 1.0f;
    str++;
  }

  for (; *str; str++) {
    if (*str >= '0' && *str <= '9') {
      if (state == 2) {
        result += (*str - '0') * fraction;
        fraction *= 0.1f;
      } else {
        result = result * 10.0f + (*str - '0');
      }
    } else if (*str == '.' && state == 0) {
      state = 2;
    } else {
      break;
    }
  }

  if (endptr) *endptr = (char *)str;

  return result * sign;
}

double expstrtof(const char *str, char **endptr) {
  double mantiss = 0.0f;
  int exp = 0;
  double sign = 1.0f;
  int state = 0;

  while (isspace(*str)) {
    str++;
  }

  if (*str == '-' || *str == '+') {
    sign = (*str == '-') ? -1.0f : 1.0f;
    str++;
  }

  for (; *str; str++) {
    if ((*str >= '0' && *str <= '9') || (state == 2 && *str == '-')) {
      if (state == 2) {
        exp = s21_strtol(str, (char **)&str, 10);
        break;
      } else {
        mantiss = pointstrtof(str, (char **)&str);
      }
    } else if ((*str == 'e' || *str == 'E') && state == 0) {
      state = 2;
    } else {
      break;
    }
  }

  if (endptr) *endptr = (char *)str;

  return mantiss * pow(10, exp) * sign;
}

long double s21_strtod(const char *str, char **endptr) {
  char *p = (char *)str;
  while (!s21_strchr(" \t\n\r", *p) && *p != '\0') {
    if (s21_strchr("eE", *p)) {
      return (long double)expstrtof(str, endptr);
    }
    p++;
  }
  return (long double)pointstrtof(str, endptr);
}

int parse_format(const char *format, char **endptr, specifier *spec) {
  int flag = 0;
  const char *p = format;
  s21_memset(spec, 0, sizeof(specifier));
  spec->width = -1;
  spec->accuracy = -1;

  while (*p && *p != '%') {
    p++;
  }
  if (!*p) return -1;

  p++;

  while (*p == '+' || *p == '-' || *p == '#' || *p == '0' || *p == ' ' ||
         *p == '*') {
    switch (*p) {
      case '+':
        spec->flags[0] = 1;
        break;
      case '-':
        spec->flags[1] = 1;
        break;
      case '#':
        spec->flags[2] = 1;
        break;
      case '0':
        spec->flags[3] = 1;
        break;
      case ' ':
        spec->flags[4] = 1;
        break;
      case '*':
        spec->width = -2;
        break;
    }
    p++;
  }

  if (*p >= '0' && *p <= '9') {
    if (spec->width == -2) spec->skip = 1;  // for sscanf: skip argument
    spec->width = s21_strtol(p, (char **)&p, 10);
  }

  if (*p == '.') {
    p++;
    if (*p == '*') {
      spec->accuracy = -2;
      p++;
    } else
      spec->accuracy = s21_strtol(p, (char **)&p, 10);
    if (spec->flags[3]) flag = 1;
    spec->flags[3] = 0;
  }

  if (*p == 'l' || *p == 'h' || *p == 'L') {
    spec->length = *p;
    p++;
  }

  spec->type = *p;

  if (spec->accuracy == -1 && s21_strchr("eEfgG", spec->type))
    spec->accuracy = 6;
  else if (spec->accuracy == -1 && s21_strchr("diuoxXpn", spec->type))
    spec->accuracy = 1;

  if (flag && s21_strchr("ofgG", spec->type)) spec->flags[3] = 1;

  if (endptr) *endptr = (char *)++p;
  return 0;
}
