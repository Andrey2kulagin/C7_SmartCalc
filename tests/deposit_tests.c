#include "test_main.h"

START_TEST(s21_deposit_1) {
  //начало второго месяца, самая первая интерация
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 2;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 1;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 0;  //раз в месяц
  deposit_initial(input, &deposit);
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(1, result_code);
  ck_assert_float_eq(deposit.body, input.deposit_initial_sum);
  ck_assert_float_eq(deposit.percents_all, deposit.percents_current);
  ck_assert_float_eq(deposit.percents_all, 63);
  ck_assert_float_eq(deposit.tax, 7.749);
}

START_TEST(s21_deposit_2) {
  //начало четвертого месяц на помесечном
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 4;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 1;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 0;  //раз в месяц
  deposit_initial(input, &deposit);
  deposit.percents_all = 126;
  deposit.percents_current = 126;
  deposit.tax = 15.53859;
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(1, result_code);
  ck_assert_float_eq(deposit.body, input.deposit_initial_sum);
  ck_assert_float_eq(deposit.percents_all, deposit.percents_current);
  ck_assert_float_eq(deposit.percents_all, 189.6615);
  ck_assert_float_eq(round(deposit.tax), 23);
}

START_TEST(s21_deposit_3) {
  //начало четвертого месяц на помесечном без капитализации
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 4;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 0;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 0;  //раз в месяц
  deposit_initial(input, &deposit);
  deposit.percents_all = 126;
  deposit.percents_current = 126;
  deposit.tax = 15.53859;
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(1, result_code);
  ck_assert_float_eq(deposit.body, input.deposit_initial_sum);
  ck_assert_float_eq(deposit.percents_all, deposit.percents_current);
  ck_assert_float_eq(deposit.percents_all, 189);
  ck_assert_float_eq(round(deposit.tax), 23);
}

START_TEST(s21_deposit_4) {
  //расчет первого начисления процентов с капитализацией и выплатой через пол
  //года
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 7;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 1;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.placement_period = 8;
  input.frequency_of_payments = 1;  //раз в 6 месяцов
  deposit_initial(input, &deposit);
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(1, result_code);
  ck_assert_float_eq(deposit.body, input.deposit_initial_sum);
  ck_assert_float_eq(deposit.percents_all, deposit.percents_current);
  ck_assert_float_eq(deposit.percents_all, 378);
  ck_assert_float_eq(deposit.tax, 46.494);
}
START_TEST(s21_deposit_5) {
  //начисление раз в пол года - четвертый месяц
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 4;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 0;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 1;  //раз в 6 месяцев
  input.placement_period = 8;
  deposit_initial(input, &deposit);
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(1, result_code);
  ck_assert_float_eq(deposit.body, input.deposit_initial_sum);
  ck_assert_float_eq(deposit.percents_all, deposit.percents_current);
  ck_assert_float_eq(deposit.percents_all, 0);
  ck_assert_float_eq(round(deposit.tax), 0);
}
START_TEST(s21_deposit_6) {
  //начисление раз в пол года - всего срок меньше, чем полгода
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 4;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 0;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 1;  //раз в 6 месяцев
  input.placement_period = 4;
  deposit_initial(input, &deposit);
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(0, result_code);
}
START_TEST(s21_deposit_7) {
  //начисление раз в год - первое начисление
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 13;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 0;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 2;  //раз в год
  input.placement_period = 12;
  deposit_initial(input, &deposit);
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(1, result_code);
  ck_assert_float_eq(deposit.body, input.deposit_initial_sum);
  ck_assert_float_eq(deposit.percents_all, deposit.percents_current);
  ck_assert_float_eq(deposit.percents_all, 756);
  ck_assert_float_eq(deposit.tax, 92.988);
}

START_TEST(s21_deposit_8) {
  //начисление раз в год - первый месяц
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 2;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 0;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 2;  //раз в год
  input.placement_period = 12;
  deposit_initial(input, &deposit);
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(1, result_code);
  ck_assert_float_eq(deposit.body, input.deposit_initial_sum);
  ck_assert_float_eq(deposit.percents_all, deposit.percents_current);
  ck_assert_float_eq(deposit.percents_all, 0);
  ck_assert_float_eq(deposit.tax, 0);
}

START_TEST(s21_deposit_9) {
  //начисление раз в год - период меньше года
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 2;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 0;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 2;  //раз в год
  input.placement_period = 1;
  deposit_initial(input, &deposit);
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(0, result_code);
}

START_TEST(s21_deposit_10) {
  //начисление в конце периода - год
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 13;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 0;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 3;  //раз в год
  input.placement_period = 12;
  deposit_initial(input, &deposit);
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(1, result_code);
  ck_assert_float_eq(deposit.body, input.deposit_initial_sum);
  ck_assert_float_eq(deposit.percents_all, deposit.percents_current);
  ck_assert_float_eq(deposit.percents_all, 756);
  ck_assert_float_eq(deposit.tax, 92.988);
}

START_TEST(s21_deposit_11) {
  //начисление в конце периода - не год
  struct deposit_input input;
  struct deposit deposit;
  int month_num = 16;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 0;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 3;  //раз в год
  input.placement_period = 15;
  deposit_initial(input, &deposit);
  int result_code = count_monthly_profit(input, &deposit, month_num);
  ck_assert_int_eq(1, result_code);
  ck_assert_float_eq(deposit.body, input.deposit_initial_sum);
  ck_assert_float_eq(deposit.percents_all, deposit.percents_current);
  ck_assert_float_eq(deposit.percents_all, 945);
  ck_assert_float_eq(deposit.tax, 116.235);
}
//тесты полного калькулятора
START_TEST(s21_deposit_12) {
  // 16 месяцев, начисление каждый месяц
  struct deposit_input input;
  struct deposit deposit;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 1;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 0;  //раз в месяц
  input.placement_period = 15;
  input.partial_withdrawal_type = 0;
  input.replanishment_type = 0;
  deposit_initial(input, &deposit);
  struct deposit_output output;
  int result_code = s21_deposit_calc(input, &output);
  ck_assert_int_eq(1, result_code);
  ck_assert_str_eq(output.anount_of_account, "12981");
  ck_assert_str_eq(output.accured_interest, "981");
  ck_assert_str_eq(output.tax_sum, "121");
}

START_TEST(s21_deposit_13) {
  // 15 месяцев, начисление процентов каждые пол года, период не кратен
  // выплатному периоду
  struct deposit_input input;
  struct deposit deposit;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 1;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 1;  //раз в пол года
  input.placement_period = 15;
  input.partial_withdrawal_type = 0;
  input.replanishment_type = 0;
  deposit_initial(input, &deposit);
  struct deposit_output output;
  int result_code = s21_deposit_calc(input, &output);
  ck_assert_int_eq(1, result_code);
  ck_assert_str_eq(output.anount_of_account, "12969");
  ck_assert_str_eq(output.accured_interest, "969");
  ck_assert_str_eq(output.tax_sum, "119");
}

START_TEST(s21_deposit_14) {
  // 15 месяцев, начисление процентов каждый год, период не кратен выплатному
  // периоду
  struct deposit_input input;
  struct deposit deposit;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 1;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 2;  //раз в год
  input.placement_period = 15;
  input.partial_withdrawal_type = 0;
  input.replanishment_type = 0;
  deposit_initial(input, &deposit);
  struct deposit_output output;
  int result_code = s21_deposit_calc(input, &output);
  ck_assert_int_eq(1, result_code);
  ck_assert_str_eq(output.anount_of_account, "12957");
  ck_assert_str_eq(output.accured_interest, "957");
  ck_assert_str_eq(output.tax_sum, "118");
}

START_TEST(s21_deposit_15) {
  // 15 месяцев, начисление процентов каждый месяц, период не кратен выплатному
  // периоду, выдача средств со счета в размере 1 тыс. каждый мес.
  struct deposit_input input;
  struct deposit deposit;
  input.deposit_initial_sum = 16000;
  input.is_capitalization = 1;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 0;  //проценты раз в мес
  input.placement_period = 15;
  input.partial_withdrawal_type = 1;  //снятие
  input.partial_withdrawal_sum = 1000;
  input.replanishment_type = 0;
  deposit_initial(input, &deposit);
  struct deposit_output output;
  int result_code = s21_deposit_calc(input, &output);
  ck_assert_int_eq(1, result_code);
  ck_assert_str_eq(output.anount_of_account, "2743");
  ck_assert_str_eq(output.accured_interest, "743");
  ck_assert_str_eq(output.tax_sum, "91");
}

START_TEST(s21_deposit_16) {
  // 15 месяцев, начисление процентов каждый месяц, период не кратен выплатному
  // периоду, выдача средств со счета в размере 1 тыс. каждый мес., пополнение
  // счета каждые 6 мес на 2 тыс.
  struct deposit_input input;
  struct deposit deposit;
  input.deposit_initial_sum = 16000;
  input.is_capitalization = 1;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 0;  //проценты раз в мес
  input.placement_period = 15;
  input.partial_withdrawal_type = 1;  //снятие
  input.partial_withdrawal_sum = 1000;
  input.replanishment_type = 2;  //пополнение
  input.replanishment_sum = 2000;
  deposit_initial(input, &deposit);
  struct deposit_output output;
  int result_code = s21_deposit_calc(input, &output);
  ck_assert_int_eq(1, result_code);
  ck_assert_str_eq(output.anount_of_account, "6872");
  ck_assert_str_eq(output.accured_interest, "872");
  ck_assert_str_eq(output.tax_sum, "107");
}

START_TEST(s21_deposit_17) {
  //Планируемое снятие больше пополнения(на счете будет отрицаительный баланс)
  struct deposit_input input;
  struct deposit deposit;
  input.deposit_initial_sum = 12000;
  input.is_capitalization = 1;
  input.tax_rate = 12.3;
  input.income_rate = 6.3;
  input.frequency_of_payments = 0;  //проценты раз в мес
  input.placement_period = 15;
  input.partial_withdrawal_type = 1;  //снятие
  input.partial_withdrawal_sum = 1000;
  deposit_initial(input, &deposit);
  struct deposit_output output;
  int result_code = s21_deposit_calc(input, &output);
  ck_assert_int_eq(0, result_code);
}

Suite *suite_s21_deposit(void) {
  Suite *s22;
  TCase *tc22;
  s22 = suite_create("s21_deposit");
  tc22 = tcase_create("case_s21_seposit");
  tcase_add_test(tc22, s21_deposit_1);
  tcase_add_test(tc22, s21_deposit_2);
  tcase_add_test(tc22, s21_deposit_3);
  tcase_add_test(tc22, s21_deposit_4);
  tcase_add_test(tc22, s21_deposit_5);
  tcase_add_test(tc22, s21_deposit_6);
  tcase_add_test(tc22, s21_deposit_7);
  tcase_add_test(tc22, s21_deposit_8);
  tcase_add_test(tc22, s21_deposit_9);
  tcase_add_test(tc22, s21_deposit_10);
  tcase_add_test(tc22, s21_deposit_11);
  tcase_add_test(tc22, s21_deposit_12);
  tcase_add_test(tc22, s21_deposit_13);
  tcase_add_test(tc22, s21_deposit_14);
  tcase_add_test(tc22, s21_deposit_15);
  tcase_add_test(tc22, s21_deposit_16);
  tcase_add_test(tc22, s21_deposit_17);
  suite_add_tcase(s22, tc22);
  return s22;
}