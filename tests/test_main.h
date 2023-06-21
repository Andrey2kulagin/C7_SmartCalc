#ifndef SRC_TESTS_TEST_MAIN_H_
#define SRC_TESTS_TEST_MAIN_H_
#include <check.h>

#include "../headers/c_libs.h"
Suite *suite_s21_validator(void);
void do_suite(Suite *suite, int *res);
Suite *suite_s21_brackets_valid(void);
Suite *suite_utils(void);
Suite *suite_s21_get_elem_type(void);
Suite *suite_s21_polish(void);
Suite *suite_s21_calculatorh(void);
Suite *suite_s21_deposit(void);
Suite *suite_s21_credit(void);
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))
#endif  //  SRC_TESTS_TEST_MAIN_H_
