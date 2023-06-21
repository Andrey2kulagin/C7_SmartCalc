#include "test_main.h"

START_TEST(s21_find_1) {
  char *input_string = "(x+2)";
  char sign = '+';
  int result = find(input_string, sign);
  ck_assert_int_eq(result, 2);
}

START_TEST(s21_find_2) {
  char *input_string = "(x+2)";
  char sign = '[';
  int result = find(input_string, sign);
  ck_assert_int_eq(result, -1);
}

START_TEST(s21_find_3) {
  char *input_string = "(x+2)";
  char sign = ')';
  int result = find(input_string, sign);
  ck_assert_int_eq(result, 4);
}

START_TEST(s21_find_4) {
  char *input_string = "(x+2)";
  char sign = '(';
  int result = find(input_string, sign);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_find_5) {
  char *input_string = "(x+2())";
  char sign = '(';
  int result = find(input_string, sign);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_rfind_1) {
  char *input_string = "(x+2())";
  char sign = '(';
  int result = rfind(input_string, sign);
  ck_assert_int_eq(result, 4);
}

START_TEST(s21_rfind_2) {
  char *input_string = "(x+2)";
  char sign = '2';
  int result = rfind(input_string, sign);
  ck_assert_int_eq(result, 3);
}

START_TEST(s21_rfind_3) {
  char *input_string = "(x+2)";
  char sign = '3';
  int result = rfind(input_string, sign);
  ck_assert_int_eq(result, -1);
}

START_TEST(s21_slice_1) {
  char *input_string = "(x+2)";
  char out_str[6] = "\0";
  int begin = 2;
  int end = 3;
  int result = slice_string(input_string, out_str, begin, end);
  ck_assert_str_eq(out_str, "+");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_slice_2) {
  char *input_string = "(x+2)";
  char out_str[6] = "\0";
  int begin = 2;
  int end = 4;
  int result = slice_string(input_string, out_str, begin, end);
  ck_assert_str_eq(out_str, "+2");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_slice_3) {
  char *input_string = "(x+2)";
  char out_str[6] = "\0";
  int begin = 6;
  int end = 9;
  int result = slice_string(input_string, out_str, begin, end);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_slice_4) {
  char *input_string = "(x+2)";
  char out_str[6] = "\0";
  int begin = 4;
  int end = 3;
  int result = slice_string(input_string, out_str, begin, end);
  ck_assert_int_eq(result, 0);
}
START_TEST(s21_slice_5) {
  char *input_string = "(x+2)";
  char out_str[6] = "\0";
  int begin = -1;
  int end = 2;
  int result = slice_string(input_string, out_str, begin, end);
  ck_assert_int_eq(result, 0);
}

Suite *suite_utils(void) {
  Suite *s22;
  TCase *tc22;
  s22 = suite_create("s21_utils");
  tc22 = tcase_create("case_utils");
  tcase_add_test(tc22, s21_find_1);
  tcase_add_test(tc22, s21_find_2);
  tcase_add_test(tc22, s21_find_3);
  tcase_add_test(tc22, s21_find_4);
  tcase_add_test(tc22, s21_rfind_1);
  tcase_add_test(tc22, s21_rfind_2);
  tcase_add_test(tc22, s21_rfind_3);
  tcase_add_test(tc22, s21_slice_1);
  tcase_add_test(tc22, s21_slice_2);
  tcase_add_test(tc22, s21_slice_3);
  tcase_add_test(tc22, s21_slice_4);
  tcase_add_test(tc22, s21_slice_5);
  suite_add_tcase(s22, tc22);
  return s22;
}