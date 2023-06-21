#include "test_main.h"

START_TEST(s21_calculator_1) {
  char *input_string = "1+2";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("3", result_str);
}

START_TEST(s21_calculator_2) {
  char *input_string = "(1.345+2)*2+(sin(12+19)+18+20)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("44.2859624", result_str);
}

START_TEST(s21_calculator_3) {
  char *input_string = "(1.345587654387512387+2)*2+(tan(12*19^2))";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("6.4291445", result_str);
}

START_TEST(s21_calculator_4) {
  char *input_string = "1 2+";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}
START_TEST(s21_calculator_5) {
  char *input_string = "1+2-18rt";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_6) {
  char *input_string = "sin()";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_7) {
  char *input_string = "sin34+2";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_8) {
  char *input_string = "sin34+2";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_9) {
  char *input_string = "1-3";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("-2", result_str);
}

START_TEST(s21_calculator_10) {
  char *input_string = "1.23*3";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("3.6900000", result_str);
}
START_TEST(s21_calculator_11) {
  char *input_string = "1.23/3";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("0.4100000", result_str);
}

START_TEST(s21_calculator_12) {
  char *input_string = "1.56^3";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("3.7964160", result_str);
}

START_TEST(s21_calculator_13) {
  char *input_string = "1.3 mod 3";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("1.3000000", result_str);
}

START_TEST(s21_calculator_14) {
  char input_string[260] = "+1*(-3)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("-3", result_str);
}

START_TEST(s21_calculator_15) {
  char input_string[260] = "-1*(-3)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("3", result_str);
}

START_TEST(s21_calculator_16) {
  char input_string[260] = "sin(123)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("-0.4599035", result_str);
}
START_TEST(s21_calculator_17) {
  char input_string[260] = "cos(123)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("-0.8879689", result_str);
}
START_TEST(s21_calculator_18) {
  char input_string[260] = "tan(123)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("0.5179275", result_str);
}

START_TEST(s21_calculator_19) {
  char input_string[260] = "acos(123)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_20) {
  char *input_string = "asin(123)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}
START_TEST(s21_calculator_21) {
  char input_string[260] = "ln(-123)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}
START_TEST(s21_calculator_22) {
  char input_string[260] = "log(-123)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_23) {
  char input_string[260] = "acos(-10)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_24) {
  char input_string[260] = "1 +/5";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_25) {
  char input_string[260] = "1/0";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_26) {
  char input_string[260] = "sqrt(-2)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_27) {
  char input_string[260] = "tan(10)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("0.6483608", result_str);
}

START_TEST(s21_calculator_28) {
  char input_string[260] = "acos(0.8)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("0.6435011", result_str);
}

START_TEST(s21_calculator_29) {
  char input_string[260] = "asin(0.8)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("0.9272952", result_str);
}

START_TEST(s21_calculator_30) {
  char input_string[260] = "atan(0.6483608)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("0.5752220", result_str);
}

START_TEST(s21_calculator_31) {
  char input_string[260] = "sqrt(0.648)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("0.8049845", result_str);
}
START_TEST(s21_calculator_32) {
  char input_string[260] = "ln(13)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("2.5649494", result_str);
}

START_TEST(s21_calculator_33) {
  char input_string[260] = "log(13)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("1.1139433", result_str);
}

START_TEST(s21_calculator_34) {
  char input_string[260] = "log(0.1)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("-1", result_str);
}
START_TEST(s21_calculator_35) {
  char input_string[260] = "ln(0)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_calculator_36) {
  char input_string[260] = "ln(5)";
  char result_str[260];
  int result = s21_calculator(input_string, result_str);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq("1.60944", result_str);
}
Suite *suite_s21_calculatorh(void) {
  Suite *s22;
  TCase *tc22;
  s22 = suite_create("s21_calculator");
  tc22 = tcase_create("case_s21_calculator");
  tcase_add_test(tc22, s21_calculator_1);
  tcase_add_test(tc22, s21_calculator_2);
  tcase_add_test(tc22, s21_calculator_3);
  tcase_add_test(tc22, s21_calculator_4);
  tcase_add_test(tc22, s21_calculator_5);
  tcase_add_test(tc22, s21_calculator_6);
  tcase_add_test(tc22, s21_calculator_7);
  tcase_add_test(tc22, s21_calculator_8);
  tcase_add_test(tc22, s21_calculator_9);
  tcase_add_test(tc22, s21_calculator_10);
  tcase_add_test(tc22, s21_calculator_11);
  tcase_add_test(tc22, s21_calculator_12);
  tcase_add_test(tc22, s21_calculator_13);
  tcase_add_test(tc22, s21_calculator_14);
  tcase_add_test(tc22, s21_calculator_15);
  tcase_add_test(tc22, s21_calculator_16);
  tcase_add_test(tc22, s21_calculator_17);
  tcase_add_test(tc22, s21_calculator_18);
  tcase_add_test(tc22, s21_calculator_19);
  tcase_add_test(tc22, s21_calculator_20);
  tcase_add_test(tc22, s21_calculator_21);
  tcase_add_test(tc22, s21_calculator_22);
  tcase_add_test(tc22, s21_calculator_23);
  tcase_add_test(tc22, s21_calculator_24);
  tcase_add_test(tc22, s21_calculator_25);
  tcase_add_test(tc22, s21_calculator_26);
  tcase_add_test(tc22, s21_calculator_27);
  tcase_add_test(tc22, s21_calculator_28);
  tcase_add_test(tc22, s21_calculator_29);
  tcase_add_test(tc22, s21_calculator_30);
  tcase_add_test(tc22, s21_calculator_31);
  tcase_add_test(tc22, s21_calculator_32);
  tcase_add_test(tc22, s21_calculator_33);
  tcase_add_test(tc22, s21_calculator_34);
  suite_add_tcase(s22, tc22);
  return s22;
}