#include "test_main.h"

START_TEST(s21_credit_1) {
  //аннуитентный
  struct credit_input input;
  input.credit_in_sum = 12000;
  input.interest_rate = 18;  // процентная ставка
  input.loan_term = 19;      // срок
  input.loan_type = 1;  //тип платежа (1 - аннуитентный, 2 - дифф.)
  struct credit_output output;
  s21_credit_calc(input, &output);
  ck_assert_str_eq(output.month_payment, "730.54");
  ck_assert_str_eq(output.over_payment, "13880");
  ck_assert_str_eq(output.total_payment, "25880");
}

START_TEST(s21_credit_2) {
  //аннуитентный
  struct credit_input input;
  input.credit_in_sum = 150000;
  input.interest_rate = 18;  // процентная ставка
  input.loan_term = 120;     // срок
  input.loan_type = 1;  //тип платежа (1 - аннуитентный, 2 - дифф.)
  struct credit_output output;
  s21_credit_calc(input, &output);
  ck_assert_str_eq(output.month_payment, "2702.78");
  ck_assert_str_eq(output.over_payment, "324333");
  ck_assert_str_eq(output.total_payment, "474333");
}

START_TEST(s21_credit_3) {
  //дифф.
  struct credit_input input;
  input.credit_in_sum = 12000;
  input.interest_rate = 12;  // процентная ставка
  input.loan_term = 12;      // срок
  input.loan_type = 2;  //тип платежа (1 - аннуитентный, 2 - дифф.)
  struct credit_output output;
  s21_credit_calc(input, &output);
  ck_assert_str_eq(output.diff_payments[0],
                   "   1120.00   |       120.00  |    1000.00");
  ck_assert_str_eq(output.diff_payments[11],
                   "   1010.00   |        10.00  |    1000.00");
  ck_assert_str_eq(output.over_payment, "780");
  ck_assert_str_eq(output.total_payment, "12780");
}

START_TEST(s21_credit_4) {
  //дифф.
  struct credit_input input;
  input.credit_in_sum = 120000000;
  input.interest_rate = 18.9358;  // процентная ставка
  input.loan_term = 719;          // срок
  input.loan_type = 2;  //тип платежа (1 - аннуитентный, 2 - дифф.)
  struct credit_output output;
  s21_credit_calc(input, &output);
  ck_assert_str_eq(output.diff_payments[0],
                   "2060478.47   |   1893580.00  |  166898.47");
  ck_assert_str_eq(output.diff_payments[718],
                   " 169532.11   |      2633.65  |  166898.47");
  ck_assert_str_eq(output.over_payment, "681688832");
  ck_assert_str_eq(output.total_payment, "801688832");
}

Suite *suite_s21_credit(void) {
  Suite *s22;
  TCase *tc22;
  s22 = suite_create("s21_credit");
  tc22 = tcase_create("case_credit");
  tcase_add_test(tc22, s21_credit_1);
  tcase_add_test(tc22, s21_credit_2);
  tcase_add_test(tc22, s21_credit_3);
  tcase_add_test(tc22, s21_credit_4);
  suite_add_tcase(s22, tc22);
  return s22;
}