#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_sscanf) {
  char test_str_s21[100], test_str_std[100];
  int test_int_s21, test_int_std;
  float test_float_s21, test_float_std;
  void *test_ptr_s21;
  void *test_ptr_std;
  int result_custom, result_standard;

  char input_str[500] = "example 123 456.789 ";
  sprintf(input_str + 20, "%p", &test_int_std);
  char format_str[] = "%s %d %f %p";

  result_custom = s21_sscanf(input_str, format_str, test_str_s21, &test_int_s21,
                             &test_float_s21, &test_ptr_s21);
  result_standard = sscanf(input_str, format_str, test_str_std, &test_int_std,
                           &test_float_std, &test_ptr_std);

  ck_assert_str_eq(test_str_s21, test_str_std);
  ck_assert_int_eq(test_int_s21, test_int_std);
  ck_assert_float_eq(test_float_s21, test_float_std);
  ck_assert_ptr_eq(test_ptr_s21, test_ptr_std);
  ck_assert_int_eq(result_custom, result_standard);

  char input_str2[] = "123456789";
  char format_str2[] = "%4d";

  result_custom = s21_sscanf(input_str2, format_str2, &test_int_s21);
  result_standard = sscanf(input_str2, format_str2, &test_int_std);

  ck_assert_int_eq(test_int_s21, test_int_std);
  ck_assert_int_eq(result_custom, result_standard);

  char input_str3[] = "0x123abc";
  char format_str3[] = "%10p";

  result_custom = s21_sscanf(input_str3, format_str3, &test_ptr_s21);
  result_standard = sscanf(input_str3, format_str3, &test_ptr_std);

  ck_assert_ptr_eq(test_ptr_s21, test_ptr_std);
  ck_assert_int_eq(result_custom, result_standard);

  char input_str4[] = "123456789";
  char format_str4[] = "%*3c%d";

  result_custom = s21_sscanf(input_str4, format_str4, &test_int_s21);
  result_standard = sscanf(input_str4, format_str4, &test_int_std);

  ck_assert_int_eq(test_int_s21, test_int_std);
  ck_assert_int_eq(result_custom, result_standard);

  char input_str5[] = "123 123.456 hello 0xff 96";
  char format_str5[] = "%*d %*f %*s %*p %d";

  result_custom = s21_sscanf(input_str5, format_str5, &test_int_s21);
  result_standard = sscanf(input_str5, format_str5, &test_int_std);

  ck_assert_int_eq(test_int_s21, test_int_std);
  ck_assert_int_eq(result_custom, result_standard);

  int test_int_s21_array[5];
  int test_int_std_array[5];
  char test_char_s21, test_char_std;

  char input_str6[] = "   123   0X83    0xff    076  34 T";
  char format_str6[] = "%i %X %x %o %u %c";

  result_custom = s21_sscanf(input_str6, format_str6, test_int_s21_array,
                             test_int_s21_array + 1, test_int_s21_array + 2,
                             test_int_s21_array + 3, test_int_s21_array + 4,
                             &test_char_s21);
  result_standard =
      sscanf(input_str6, format_str6, test_int_std_array,
             test_int_std_array + 1, test_int_std_array + 2,
             test_int_std_array + 3, test_int_std_array + 4, &test_char_std);

  for (int i = 0; i < 5; i++) {
    ck_assert_int_eq(test_int_s21_array[i], test_int_std_array[i]);
  }
  ck_assert_int_eq(test_char_s21, test_char_std);
  ck_assert_int_eq(result_custom, result_standard);
}
END_TEST