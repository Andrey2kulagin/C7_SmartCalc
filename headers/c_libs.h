#ifndef SRC_S21_C_LIBS_H_
#define SRC_S21_C_LIBS_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//структуры
struct credit_input {
  double credit_in_sum;  //общая сумма double
  int loan_term;         // срок int
  double interest_rate;  // процентная ставка double
  int loan_type;         // тип int
};

struct credit_output {
  char month_payment[280];  //месячная плата double
  char over_payment[280];   // переплата double
  char total_payment[280];  // общая выплата double
  char diff_payments[1024]
                    [280];  // список строк для диффиренцированного платежа
  int diff_payments_count;  // каунтер для списка платежей
};
struct deposit {
  double body;  //тело депозита остаток с учетов вычета
  double percents_current;  //текущий остаток по процентам
  double tax;               //сумма по налогам
  double percents_all;      //сумма по процентам
};
struct deposit_input {
  double deposit_initial_sum;  // входящая сумма double
  int placement_period;        // срок размещения int
  double income_rate;          //процентная ставка double
  double tax_rate;             //налог double
  int frequency_of_payments;   //периодичность выплат int
  int is_capitalization;     //капитализация процентов int
  int replanishment_type;    // пополнения int
  double replanishment_sum;  //сумма пополнения double
  int partial_withdrawal_type;    // снятия int
  double partial_withdrawal_sum;  // сумма снятия double
};

struct deposit_output {
  char accured_interest[280];  // начисленные проценты double
  char tax_sum[280];           // сумма налога double
  char anount_of_account[280];  //сумма на вкладе на конец double
};

//основнык функции
/**
 * @brief основная функция калькулятора
 * 
 * @param input выражение в инфиксной форме
 * @param result_str результат
 * @return int  код результата, 1 - все норм. 0 - ошибка
 */
int s21_calculator(char *input, char *result_str);
/**
 * @brief валидатор выражений, валидирует только скобки
 * 
 * @param input_string 
 * @return int 
 */
int s21_numeric_expression_validator(char *input_string);
/**
 * @brief  переводчик в польскую нотацию
 * 
 * @param input_string  
 * @param output 
 * @return int 
 */
int to_polish(char *input_string, char *output);
/**
 * @brief получение результата из польской нотации
 * 
 * @param polish 
 * @param output 
 * @return int 
 */
int s21_get_result_from_polish(char *polish, char *output);
/**
 * @brief калькуляция с икс
 * 
 * @param input 
 * @param result_str 
 * @param x_value 
 * @return int 
 */
int s21_calculator_with_x(char *input, char *result_str, char *x_value);
/**
 * @brief калькуляция для графика
 * 
 * @param input 
 * @param result_double 
 * @param x_value 
 * @return int 
 */
int s21_calculator_to_chart(char *input, double *result_double, char *x_value);
/**
 * @brief депозмитный калькулятор
 * 
 * @param input 
 * @param output 
 * @return int 
 */
int s21_deposit_calc(struct deposit_input input, struct deposit_output *output);
/**
 * @brief кредитный калькулятор
 * 
 * @param input 
 * @param output 
 */
void s21_credit_calc(struct credit_input input, struct credit_output *output);

// credit utils
void annuity_credit_handler(struct credit_input input,
                            struct credit_output *output);
void differentiated_credit_handler(struct credit_input input,
                                   struct credit_output *output);

// deposit_utils
int count_monthly_profit(struct deposit_input input, struct deposit *deposit,
                         int month_num);
void deposit_initial(struct deposit_input input, struct deposit *deposit);
void set_persents_and_tax(struct deposit_input input, struct deposit *deposit,
                          double months_value, double amount_for_calculating);
void count_monthly_replanishment(struct deposit_input input,
                                 struct deposit *deposit, int month_num);
void calc_partial_withdrawal(struct deposit_input input,
                             struct deposit *deposit);
int count_monthly_partial_withdrawal(struct deposit_input input,
                                     struct deposit *deposit, int month_num);
void from_deposit_to_output(struct deposit deposit,
                            struct deposit_output *output);

// utils
int is_brakets_valid(char *input_string);
int is_true_sign(char *input_string_orig);
int check_x(char *input_string, int i);
int is_trig_value_true(char *input_string);
int is_trig_value_empty(char *input_string, int i, int input_length);
int get_elem_type(char *buffer);
int is_number(char *buffer);
int element_parsing(char *input_string, int *i, int input_length, char *output,
                    char *stack);
void close_bracket_handler(char *stack, char *output);
void sign_handler(char *stack, char *output, char sign);
void reverse(char *input);
void separator_append(char *output);
char get_trig_code(char *buffer);
void del_sign(char *input_str, size_t sign_number);
void append_sign_to_str(char *input_str, char sign, size_t pos);
void unary_signs_normalize(char *input_str);
int from_polish_operator_handler(char *buffer, char stack[260][260],
                                 int *stack_counter);
int operator_handler(char stack[260][260], int *stack_counter, char *buffer);
int trig_handler(char stack[260][260], int stack_counter, char *buffer);
void result_round(char *result_str);
void replace_x(char *input_str, char *to);
// python utils
int find(char *input_string, char find_char);
int rfind(char *input_string, char find_char);
int slice_string(char *input_string, char *out_string, int begin, int end);
int count_c(char *input_string_orig, char find_char);
void append(char *input_string_orig, char append_sign);
int str_in_trig_arr(char *input_string_orig);
int is_char_in_str(char *input_string_orig, char sign);
#ifdef __cplusplus
}
#endif
#endif  // SRC_S21_C_LIBS_H_
