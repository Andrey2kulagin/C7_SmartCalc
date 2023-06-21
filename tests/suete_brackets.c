#include "test_main.h"

START_TEST(s21_brackets_1) {
  char *input_string = "(x+2)";

  int result = is_brakets_valid(input_string);
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_brackets_2) {
  char *input_string = "()x+2";

  int result = is_brakets_valid(input_string);
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_brackets_3) {
  char *input_string = "(x+2";

  int result = is_brakets_valid(input_string);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_brackets_4) {
  char *input_string = "(x)+2";

  int result = is_brakets_valid(input_string);
  ck_assert_int_eq(result, 1);
}
START_TEST(s21_brackets_5) {
  char *input_string = "()+()";

  int result = is_brakets_valid(input_string);
  ck_assert_int_eq(result, 1);
}
START_TEST(s21_brackets_6) {
  char *input_string = "(12+(13))";

  int result = is_brakets_valid(input_string);
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_brackets_7) {
  char *input_string = "))((12+13";

  int result = is_brakets_valid(input_string);
  ck_assert_int_eq(result, 0);
}

Suite *suite_s21_brackets_valid(void) {
  Suite *s22;
  TCase *tc22;
  s22 = suite_create("s21_brackets");
  tc22 = tcase_create("case_brackets");
  tcase_add_test(tc22, s21_brackets_1);
  tcase_add_test(tc22, s21_brackets_2);
  tcase_add_test(tc22, s21_brackets_3);
  tcase_add_test(tc22, s21_brackets_4);
  tcase_add_test(tc22, s21_brackets_5);
  tcase_add_test(tc22, s21_brackets_6);
  tcase_add_test(tc22, s21_brackets_7);
  suite_add_tcase(s22, tc22);
  return s22;
}