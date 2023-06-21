#include "test_main.h"

START_TEST(s21_get_elem_type_1) {
  char *input_string = "365";
  int result = get_elem_type(input_string);
  ck_assert_int_eq(result, 1);
}
START_TEST(s21_get_elem_type_2) {
  char *input_string = "3.2";
  int result = get_elem_type(input_string);
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_get_elem_type_3) {
  char *input_string = "sin";
  int result = get_elem_type(input_string);
  ck_assert_int_eq(result, 2);
}

START_TEST(s21_get_elem_type_4) {
  char *input_string = "12 sin";
  int result = get_elem_type(input_string);
  ck_assert_int_eq(result, 3);
}
START_TEST(s21_get_elem_type_5) {
  char *input_string = "smn";
  int result = get_elem_type(input_string);
  ck_assert_int_eq(result, 3);
}

START_TEST(s21_is_number_1) {
  char *input_string = "12";
  int result = is_number(input_string);
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_is_number_2) {
  char *input_string = "1.2";
  int result = is_number(input_string);
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_is_number_3) {
  char *input_string = "sin";
  int result = is_number(input_string);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_is_number_4) {
  char *input_string = "siwn";
  int result = is_number(input_string);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_is_number_5) {
  char *input_string = "";
  int result = is_number(input_string);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_is_trig_1) {
  char *input_string = "sin";
  int result = str_in_trig_arr(input_string);
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_is_trig_2) {
  char *input_string = "cos";
  int result = str_in_trig_arr(input_string);
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_is_trig_3) {
  char *input_string = "12";
  int result = str_in_trig_arr(input_string);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_is_trig_4) {
  char *input_string = "";
  int result = str_in_trig_arr(input_string);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_element_parsing_1) {
  char *input_string = "(2+3)";
  char output[260] = "\0";
  int i = 1;
  int input_length = 5;
  char stack[260] = "\0";
  int res = element_parsing(input_string, &i, input_length, output, stack);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(i, 1);
  ck_assert_str_eq("2", output);
}



START_TEST(s21_element_parsing_3) {
  char stack[260] = "\0";
  char *input_string = "(son(23)+3)";
  char output[260] = "\0";
  int i = 1;
  int input_length = 10;
  int res = element_parsing(input_string, &i, input_length, output, stack);
  ck_assert_int_eq(res, 0);
}


START_TEST(s21_element_parsing_5) {
  char stack[260] = "\0";
  char *input_string = "(son (23)+3)";
  char output[260] = "\0";
  int i = 1;
  int input_length = 10;
  int res = element_parsing(input_string, &i, input_length, output, stack);
  ck_assert_int_eq(res, 0);
}

Suite *suite_s21_get_elem_type(void) {
  Suite *s22;
  TCase *tc22;
  s22 = suite_create("s21_get_elem_type");
  tc22 = tcase_create("case_get_elem_type");
  tcase_add_test(tc22, s21_get_elem_type_1);
  tcase_add_test(tc22, s21_get_elem_type_2);
  tcase_add_test(tc22, s21_get_elem_type_3);
  tcase_add_test(tc22, s21_get_elem_type_4);
  tcase_add_test(tc22, s21_get_elem_type_5);

  tcase_add_test(tc22, s21_is_number_1);
  tcase_add_test(tc22, s21_is_number_2);
  tcase_add_test(tc22, s21_is_number_3);
  tcase_add_test(tc22, s21_is_number_4);
  tcase_add_test(tc22, s21_is_number_5);

  tcase_add_test(tc22, s21_is_trig_1);
  tcase_add_test(tc22, s21_is_trig_2);
  tcase_add_test(tc22, s21_is_trig_3);
  tcase_add_test(tc22, s21_is_trig_4);
  tcase_add_test(tc22, s21_element_parsing_1);
  tcase_add_test(tc22, s21_element_parsing_3);
  tcase_add_test(tc22, s21_element_parsing_5);
  suite_add_tcase(s22, tc22);
  return s22;
}