#include <check.h>
#include <limits.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_sprintf) {
  char custom[500];
  char standard[500];

  char str[] = "%+d %+-0#*.*ld %#03.2x %#0.*x";

  sprintf(standard, str, 5, 20, 10, -3, -123, 10, 125);
  s21_sprintf(custom, str, 5, 20, 10, -3, -123, 10, 125);

  ck_assert_str_eq(custom, standard);

  char str1[] = "%+f %+#0*.*Lf %0.2f";

  sprintf(standard, str1, 5.3, 20, 10, 3.L, -98.123151352123245);
  s21_sprintf(custom, str1, 5.3, 20, 10, 3.L, -98.123151352123245);

  ck_assert_str_eq(custom, standard);

  char str2[] = "%d %ld %u %#x %#o %+f %le %g %+10.3f %-10s %c";
  sprintf(standard, str2, INT_MIN, LONG_MAX, UINT_MAX, 0xff, 075, -123.456,
          1234567.89, 123.456789, 3.14159, "hello world", 'A');
  s21_sprintf(custom, str2, INT_MIN, LONG_MAX, UINT_MAX, 0xff, 075, -123.456,
              1234567.89, 123.456789, 3.14159, "hello world", 'A');
  ck_assert_str_eq(custom, standard);

  char str3[] = "%-10lo %f %f %20.5s %-.10s";
  double nanValue = NAN;
  double infValue = -INFINITY;
  sprintf(standard, str3, 255, nanValue, infValue, "  spaced string  ",
          "trimming");
  s21_sprintf(custom, str3, 255, nanValue, infValue, "  spaced string",
              "trimming");
  ck_assert_str_eq(custom, standard);

  char str4[] = "%+10d %05u %lu %hu %-#8x %10.3e %*.*f %-10c";
  sprintf(standard, str4, -42, 42, 42, 42, 0xbeef, 0.123456, 8, 2, 3.14159265,
          'T');
  s21_sprintf(custom, str4, -42, 42, 42, 42, 0xbeef, 0.123456, 8, 2, 3.14159265,
              'T');
  ck_assert_str_eq(custom, standard);

  char str5[] = "%p %0#10p %g %10.3g %+-0# % %% %n";
  int k, n;
  sprintf(standard, str5, str5, NULL, 123.456, 123324324.456, &k);
  s21_sprintf(custom, str5, str5, NULL, 123.456, 123324324.456, &n);
  ck_assert_str_eq(custom, standard);
  ck_assert_int_eq(k, n);
}
END_TEST