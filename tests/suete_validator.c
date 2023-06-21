#include "test_main.h"

START_TEST(s21_validator_2) {
  char *input_string = "(1+2)";

  int result = s21_numeric_expression_validator(input_string);
  ck_assert_int_eq(result, 1);
}
START_TEST(s21_validator_3) {
  char *input_string = "1+2)";

  int result = s21_numeric_expression_validator(input_string);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_validator_4) {
  char *input_string = "1(+2)";

  int result = s21_numeric_expression_validator(input_string);
  ck_assert_int_eq(result, 1);
}
START_TEST(s21_validator_5) {
  char *input_string = "(1+2)";

  int result = s21_numeric_expression_validator(input_string);
  ck_assert_int_eq(result, 1);
}
START_TEST(s21_validator_6) {
  char *input_string = "(sin(1)+2)";

  int result = s21_numeric_expression_validator(input_string);
  ck_assert_int_eq(result, 1);
}
START_TEST(s21_validator_8) {
  char *input_string = "))(((sin(2))+2";

  int result = s21_numeric_expression_validator(input_string);
  ck_assert_int_eq(result, 0);
}
START_TEST(s21_validator_9) {
  char *input_string =
      "cos(1)+sin(1)*tan(x)+acos(x)-asin(x)+atan(x)*sqrt(x)-ln(x)+log(x)";

  int result = s21_numeric_expression_validator(input_string);
  ck_assert_int_eq(result, 1);
}

Suite *suite_s21_validator(void) {
  Suite *s22;
  TCase *tc22;
  s22 = suite_create("s21_validator");
  tc22 = tcase_create("case_validator");
  tcase_add_test(tc22, s21_validator_2);
  tcase_add_test(tc22, s21_validator_3);
  tcase_add_test(tc22, s21_validator_4);
  tcase_add_test(tc22, s21_validator_5);
  tcase_add_test(tc22, s21_validator_6);
  tcase_add_test(tc22, s21_validator_8);
  tcase_add_test(tc22, s21_validator_9);
  suite_add_tcase(s22, tc22);
  return s22;
}