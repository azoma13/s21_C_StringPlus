#ifndef COMMON_H
#define COMMON_H

typedef struct specifier {
  char type;
  int flags[5];
  int width;
  int accuracy;
  char length;
  char skip;
} specifier;

void reverse_string(char* start, int length);
void intToString(char* buffer, long int number, specifier spec);
void floatToString(char* buffer, long double value, specifier spec);
int get_exp(long double value);
long long get_mantissa(long double value, int precision);
void floatToScientificString(char* buffer, long double value, int precision,
                             char ch, int point);
int parse_format(const char* format, char** endptr, specifier* spec);
long int s21_strtol(const char* str, char** endptr, int base);
long double s21_strtod(const char* str, char** endptr);

#endif