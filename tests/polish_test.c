#include "test_main.h"

START_TEST(s21_polish_1) {
  char stack[260] = "+-+(*-+*";
  char output[260] = "365";
  close_bracket_handler(stack, output);
  ck_assert_str_eq("365;*;+;-;*", output);
}

START_TEST(s21_polish_2) {
  char input[260] = "sin(1+3*6*(1+2))+12";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq("1;3;6;*;1;2;+;*;+;s;12;+", output);
}

START_TEST(s21_polish_3) {
  char input[260] = "sin((1+3)*6*(1+2))+12";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq("1;3;+;6;*;1;2;+;*;s;12;+", output);
}

START_TEST(s21_polish_4) {
  char input[260] = "sin((1+3)*6*(1+2))+(cos(12)*29+79)";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq("1;3;+;6;*;1;2;+;*;s;12;c;29;*;79;+;+", output);
}
START_TEST(s21_polish_5) {
  char input[260] = "12 mod 2 *sin((1+3)*6*(1+2))+((cos(12)*29)+79)";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq("12;2;%;1;3;+;6;*;1;2;+;*;s;*;12;c;29;*;79;+;+", output);
}

START_TEST(s21_polish_6) {
  char input[260] = "12 mod 2 *sin((1+3^9)*6*(1+2))+cos(12)*(29+79)";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq("12;2;%;1;3;9;^;+;6;*;1;2;+;*;s;*;12;c;29;79;+;*;+", output);
}

START_TEST(s21_polish_7) {
  char input[260] = "12 mod 2 *sin((1+3^9)*6.345*(1+2))+cos(12.18)*(29+79)";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq("12;2;%;1;3;9;^;+;6.345;*;1;2;+;*;s;*;12.18;c;29;79;+;*;+",
                   output);
}

START_TEST(s21_polish_8) {
  char input[260] = "12 md 2 *sin((1+3^9)*6.345*(1+2))+cos(12.18)*(29+79)";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(0, result_status);
}

START_TEST(s21_polish_10) {
  char input[260] = "12 mod 2sin((1+3^9)*6.345*(1+2))+cos(12.18)*(29+79)";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(0, result_status);
}

START_TEST(s21_polish_9) {
  char input[260] = "12 mod 2 *sin((1+3^9)*6.345^3*(1+2))+cos(12.18)*(29+79)";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq(
      "12;2;%;1;3;9;^;+;6.345;3;^;*;1;2;+;*;s;*;12.18;c;29;79;+;*;+", output);
}

START_TEST(s21_polish_11) {
  char input[260] = "-12+(-13)^3*12-16+7";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq("0;12;-;0;13;-;3;^;12;*;+;16;-;7;+", output);
}

START_TEST(s21_polish_12) {
  char input[260] = "-12+13^3*(-12-16)+7";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq("0;12;-;13;3;^;0;12;-;16;-;*;+;7;+", output);
}

START_TEST(s21_polish_13) {
  char input[260] = "-12-13^2*13-16+7";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq("0;12;-;13;2;^;13;*;-;16;-;7;+", output);
}

START_TEST(s21_polish_14) {
  char input[260] = "x+12";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq("x;12;+", output);
}

START_TEST(s21_polish_15) {
  char input[260] = "12 mod x *sin((1+3^x)*6.345^3*(1+x))+cos(12.18)*(29+79)";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(1, result_status);
  ck_assert_str_eq(
      "12;x;%;1;3;x;^;+;6.345;3;^;*;1;x;+;*;s;*;12.18;c;29;79;+;*;+", output);
}

START_TEST(s21_polish_16) {
  char input[260] = "12 md x";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(0, result_status);
}
START_TEST(s21_polish_17) {
  char input[260] = "()12 + 1)";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(0, result_status);
}
START_TEST(s21_polish_18) {
  char input[260] = "(12 + x 1)";
  char output[260] = "\0";
  int result_status = to_polish(input, output);
  ck_assert_int_eq(0, result_status);
}

Suite *suite_s21_polish(void) {
  Suite *s22;
  TCase *tc22;
  s22 = suite_create("s21_polish_notation");
  tc22 = tcase_create("case_polish_notation");
  tcase_add_test(tc22, s21_polish_1);
  tcase_add_test(tc22, s21_polish_2);
  tcase_add_test(tc22, s21_polish_3);
  tcase_add_test(tc22, s21_polish_4);
  tcase_add_test(tc22, s21_polish_5);
  tcase_add_test(tc22, s21_polish_6);
  tcase_add_test(tc22, s21_polish_7);
  tcase_add_test(tc22, s21_polish_8);
  tcase_add_test(tc22, s21_polish_9);
  tcase_add_test(tc22, s21_polish_10);
  tcase_add_test(tc22, s21_polish_11);
  tcase_add_test(tc22, s21_polish_12);
  tcase_add_test(tc22, s21_polish_13);
  tcase_add_test(tc22, s21_polish_14);
  tcase_add_test(tc22, s21_polish_15);
  tcase_add_test(tc22, s21_polish_16);
  tcase_add_test(tc22, s21_polish_17);
  tcase_add_test(tc22, s21_polish_18);
  suite_add_tcase(s22, tc22);
  return s22;
}