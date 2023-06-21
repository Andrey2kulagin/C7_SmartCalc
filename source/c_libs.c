#include "../headers/c_libs.h"

void s21_credit_calc(struct credit_input input, struct credit_output *output) {
  if (input.loan_type == 1) {
    //аннуитентный
    // просто считаем проценты и делим все на кол-во месяцев
    annuity_credit_handler(input, output);
  } else {
    if (input.loan_type == 2) {
      //дифференцированный
      // считаем помесячно
      differentiated_credit_handler(input, output);
    }
  }
}
void differentiated_credit_handler(struct credit_input input,
                                   struct credit_output *output) {
  int month_num = 2;
  double my_credit_body = input.credit_in_sum;
  int output_counter = 0;
  double percent_per_month = input.interest_rate / 100.0 / 12.0;
  float credit_body_part = input.credit_in_sum / input.loan_term;
  float all_percents = 0;
  while (month_num <= input.loan_term + 1) {
    double cure_percent = my_credit_body * percent_per_month;
    double cure_payment = credit_body_part + cure_percent;
    sprintf(output->diff_payments[output_counter],
            "%10.2lf   |   %10.2lf  | %10.2lf", cure_payment, cure_percent,
            credit_body_part);  //всего платеж; проценты; тело кредита
    output_counter++;
    my_credit_body -= credit_body_part;
    all_percents += cure_percent;
    month_num++;
  }
  sprintf(output->over_payment, "%.0lf", all_percents);
  sprintf(output->total_payment, "%.0lf", input.credit_in_sum + all_percents);
  output->diff_payments_count = output_counter;
}
void annuity_credit_handler(struct credit_input input,
                            struct credit_output *output) {
  double percent_per_month = input.interest_rate / 100.0 / 12.0;
  double k =
      (percent_per_month * powf(1 + percent_per_month, input.loan_term)) /
      (powf(1 + percent_per_month, input.loan_term) - 1);
  double percent_value_for_month = input.credit_in_sum * k;
  double percent_sum = percent_value_for_month * input.loan_term;
  sprintf(output->month_payment, "%.2lf", percent_value_for_month);
  sprintf(output->over_payment, "%.0lf", percent_sum);
  sprintf(output->total_payment, "%.0lf", percent_sum + input.credit_in_sum);
}

int s21_deposit_calc(struct deposit_input input,
                     struct deposit_output *output) {
  int result = 1;
  int month_num =
      2;  //начинаем считать с 2, т.к. расчетное время - начало 2-го месяца
  struct deposit deposit;
  deposit_initial(input, &deposit);
  while (month_num <= input.placement_period + 1 && result) {
    //считаем проценты за прошедший месяц
    result *= count_monthly_profit(input, &deposit, month_num);
    //считаем все внесения в месяце
    count_monthly_replanishment(input, &deposit, month_num);

    // считаем все списания в месяце
    result *= count_monthly_partial_withdrawal(input, &deposit, month_num);
    month_num++;
  }
  from_deposit_to_output(deposit, output);

  return result;
}

void from_deposit_to_output(struct deposit deposit,
                            struct deposit_output *output) {
  sprintf(output->accured_interest, "%.0lf", deposit.percents_all);
  sprintf(output->anount_of_account, "%.0lf",
          deposit.body + deposit.percents_current);
  sprintf(output->tax_sum, "%.0lf", deposit.tax);
}
int count_monthly_partial_withdrawal(struct deposit_input input,
                                     struct deposit *deposit, int month_num) {
  if (input.partial_withdrawal_type != 0 &&
      month_num - 1 != input.placement_period) {
    if (input.partial_withdrawal_type == 1) {
      //раз в месяц
      calc_partial_withdrawal(input, deposit);
    }
    if (input.partial_withdrawal_type == 2) {
      //раз в полгода
      if ((month_num - 1) % 6 == 0) {
        calc_partial_withdrawal(input, deposit);
      }
    }
    if (input.partial_withdrawal_type == 3) {
      // раз в год
      if ((month_num - 1) % 12 == 0) {
        calc_partial_withdrawal(input, deposit);
      }
    }
  }
  return deposit->body > 0;
}
void calc_partial_withdrawal(struct deposit_input input,
                             struct deposit *deposit) {
  double operation_result =
      deposit->percents_current - input.partial_withdrawal_sum;
  if (operation_result < 0) {
    deposit->percents_current = 0;
    deposit->body += operation_result;
  } else {
    deposit->percents_current = operation_result;
  }
}

void count_monthly_replanishment(struct deposit_input input,
                                 struct deposit *deposit, int month_num) {
  if (input.replanishment_type != 0 &&
      month_num - 1 != input.placement_period) {
    if (input.replanishment_type == 1) {
      // 1 раз в месяц
      deposit->body += input.replanishment_sum;
    }
    if (input.replanishment_type == 2) {
      // 1 раз в пол года
      if ((month_num - 1) % 6 == 0) {
        deposit->body += input.replanishment_sum;
      }
    }
    if (input.replanishment_type == 3) {
      // 1 раз в год
      if ((month_num - 1) % 12 == 0) {
        deposit->body += input.replanishment_sum;
      }
    }
  }
}

void deposit_initial(struct deposit_input input, struct deposit *deposit) {
  deposit->body = input.deposit_initial_sum;
  deposit->percents_all = 0;
  deposit->percents_current = 0;
  deposit->tax = 0;
}
int count_monthly_profit(struct deposit_input input, struct deposit *deposit,
                         int month_num) {
  double amount_for_calculating = 0;
  int result = 1;
  if (input.is_capitalization) {
    amount_for_calculating = deposit->body + deposit->percents_current;
  } else {
    amount_for_calculating = deposit->body;
  }
  if (input.frequency_of_payments == 0) {
    //раз в месяц
    set_persents_and_tax(input, deposit, 12, amount_for_calculating);
  }
  if (input.frequency_of_payments == 1) {
    // раз в 6 месяцев
    if (input.placement_period < 6) {
      result = 0;
    } else {
      if ((month_num - 1) % 6 == 0) {
        set_persents_and_tax(input, deposit, 2, amount_for_calculating);
      } else {
        if (month_num - 1 == input.placement_period) {
          set_persents_and_tax(input, deposit, 12 / ((month_num - 1) % 6),
                               amount_for_calculating);
        }
      }
    }
  }
  if (input.frequency_of_payments == 2) {
    // раз в год
    if (input.placement_period < 12) {
      result = 0;
    } else {
      if ((month_num - 1) % 12 == 0) {
        set_persents_and_tax(input, deposit, 1, amount_for_calculating);
      } else {
        if (month_num - 1 == input.placement_period) {
          set_persents_and_tax(input, deposit, 12 / ((month_num - 1) % 12),
                               amount_for_calculating);
        }
      }
    }
  }
  if (input.frequency_of_payments == 3) {
    // в конце
    if (input.placement_period == month_num - 1) {
      set_persents_and_tax(input, deposit, 12.0 / input.placement_period,
                           amount_for_calculating);
    }
  }
  return result;
}
void set_persents_and_tax(struct deposit_input input, struct deposit *deposit,
                          double months_value, double amount_for_calculating) {
  double rate_percent = input.income_rate / 100 / months_value;
  double percents = amount_for_calculating * (rate_percent);
  deposit->percents_all += percents;
  deposit->percents_current += percents;
  deposit->tax += percents * input.tax_rate / 100;
}

int s21_calculator_with_x(char *input, char *result_str, char *x_value) {
  replace_x(input, x_value);
  return s21_calculator(input, result_str);
}

int s21_calculator_to_chart(char *input, double *result_double, char *x_value) {
  char result_str[260] = "\0";
  int result_code = s21_calculator_with_x(input, result_str, x_value);
  if (result_code) {
    sscanf(result_str, "%lf", result_double);
  }
  return result_code;
}
void replace_x(char *input_str, char *to) {
  int x_index = find(input_str, 'x');
  while (x_index != -1) {
    char left[1024] = "\0";
    char rigth[1024] = "\0";
    slice_string(input_str, left, 0, x_index);
    slice_string(input_str, rigth, x_index + 1, strlen(input_str));
    append(left, '(');
    strcat(left, to);
    append(left, ')');
    strcat(left, rigth);
    strcpy(input_str, left);
    x_index = find(input_str, 'x');
  }
}
int s21_calculator(char *input, char *result_str) {
  int result = 1;
  char polish[270] = "\0";
  result *= to_polish(input, polish);
  result *= s21_get_result_from_polish(polish, result_str);
  result_round(result_str);
  return result;
}
void result_round(char *result_str) {
  int is_point = 0;
  int is_all_null = 1;
  double number = 0;
  sscanf(result_str, "%lf", &number);
  sprintf(result_str, "%.7lf", number);
  for (int i = 0; i < (int)strlen(result_str); i++) {
    if (is_point) {
      if (result_str[i] != '0') {
        is_all_null = 0;
      }
    }
    if (result_str[i] == '.') {
      is_point = 1;
    }
  }
  if (is_all_null) {
    char buffer[260] = "\0";
    slice_string(result_str, buffer, 0, find(result_str, '.'));
    strcpy(result_str, buffer);
  }
}
int s21_get_result_from_polish(char *polish, char *result_str) {
  int polish_len = strlen(polish);
  char buffer[260] = "\0";
  int buffer_index = 0;
  char stack[260][260];
  int stack_counter = 0;
  int result = 1;
  int i = 0;
  while (i < polish_len && result) {
    if (i == polish_len - 1) {
      buffer[buffer_index] = polish[i];
      buffer[buffer_index + 1] = '\0';
      buffer_index++;
    }
    if (polish[i] == ';' || i == polish_len - 1) {
      if (is_number(buffer)) {
        strcpy(stack[stack_counter], buffer);
        stack_counter++;
      } else {
        result *= from_polish_operator_handler(buffer, stack, &stack_counter);
      }
      buffer_index = 0;
      buffer[0] = '\0';
    } else {
      buffer[buffer_index] = polish[i];
      buffer[buffer_index + 1] = '\0';
      buffer_index++;
    }
    i++;
  }
  strcpy(result_str, stack[0]);
  return result;
}

int from_polish_operator_handler(char *buffer, char stack[260][260],
                                 int *stack_counter) {
  //обрабатывает польскую нотацию с уже замененным x
  int result = 1;

  if (is_char_in_str((char *)"sctCSTqlL", buffer[0])) {
    if (*stack_counter < 1) {
      result = 0;
    }
    result *= trig_handler(stack, *stack_counter, buffer);
  } else {
    if (is_char_in_str((char *)"+-*%/^", buffer[0])) {
      if (*stack_counter < 2) {
        result = 0;
      }
      result *= operator_handler(stack, stack_counter, buffer);
    } else {
      if (is_number(buffer) == 0) {
        result = 0;
      } else {
        double number = 0;
        sscanf(buffer, "%lf", &number);
        sprintf(buffer, "%.7lf", number);
        strcpy(stack[*stack_counter], buffer);
        *stack_counter += 1;
      }
    }
  }
  return result;
}
int operator_handler(char stack[260][260], int *stack_counter, char *buffer) {
  double left_number = 0;
  double rigth_number = 0;
  int result = 1;
  char operation_result[260] = "\0";
  sscanf(stack[*stack_counter - 2], "%lf", &left_number);
  sscanf(stack[*stack_counter - 1], "%lf", &rigth_number);
  if (strcmp(buffer, "+") == 0) {
    sprintf(operation_result, "%.15lf", left_number + rigth_number);
  }
  if (strcmp(buffer, "-") == 0) {
    sprintf(operation_result, "%.15lf", left_number - rigth_number);
  }
  if (strcmp(buffer, "*") == 0) {
    sprintf(operation_result, "%.15lf", left_number * rigth_number);
  }
  if (strcmp(buffer, "/") == 0) {
    double epsilon = 0.000000001;
    if (fabs(rigth_number - 0.0) < epsilon) {
      result = 0;
    }
    sprintf(operation_result, "%.15lf", left_number / rigth_number);
  }
  if (strcmp(buffer, "%") == 0) {
    sprintf(operation_result, "%.15lf", fmod(left_number, rigth_number));
  }
  if (strcmp(buffer, "^") == 0) {
    sprintf(operation_result, "%.15lf", pow(left_number, rigth_number));
  }
  strcpy(stack[*stack_counter - 2], operation_result);
  *stack_counter -= 1;
  return result;
}
int trig_handler(char stack[260][260], int stack_counter, char *buffer) {
  char operation_result[260] = "\0";
  double number_float = 0;
  int result = 1;
  sscanf(stack[stack_counter - 1], "%lf", &number_float);
  if (strcmp(buffer, "s") == 0) {
    sprintf(operation_result, "%.15lf", sin(number_float));
  }
  if (strcmp(buffer, "c") == 0) {
    sprintf(operation_result, "%.15lf", cos(number_float));
  }
  if (strcmp(buffer, "t") == 0) {
    if (fabs(fabs(fmod(number_float, 3.14)) - 1.57) == 0) {
      result = 0;
    }
    sprintf(operation_result, "%.15lf", tan(number_float));
  }
  if (strcmp(buffer, "C") == 0) {
    if (number_float < -1 || number_float > 1) {
      result = 0;
    }
    sprintf(operation_result, "%.15lf", acos(number_float));
  }
  if (strcmp(buffer, "S") == 0) {
    if (number_float < -1 || number_float > 1) {
      result = 0;
    }
    sprintf(operation_result, "%.15lf", asin(number_float));
  }
  if (strcmp(buffer, "T") == 0) {
    sprintf(operation_result, "%.15lf", atan(number_float));
  }
  if (strcmp(buffer, "q") == 0) {
    if (number_float < 0) {
      result = 0;
    }
    sprintf(operation_result, "%.15lf", sqrt(number_float));
  }
  if (strcmp(buffer, "l") == 0) {
    if (number_float <= 0) {
      result = 0;
    }
    sprintf(operation_result, "%.15lf", log(number_float));
  }
  if (strcmp(buffer, "L") == 0) {
    if (number_float <= 0) {
      result = 0;
    }
    sprintf(operation_result, "%.15lf", log10f(number_float));
  }

  strcpy(stack[stack_counter - 1], operation_result);
  return result;
}

int to_polish(char *input_string, char *output) {
  char stack[260] = "\0";
  unary_signs_normalize(input_string);
  int result = 1;
  result *= s21_numeric_expression_validator(input_string);
  int input_length = strlen(input_string);

  int i = 0;

  // формируем элемент
  while (i < input_length && result) {
    if (is_char_in_str((char *)"()", input_string[i]) ||
        is_char_in_str((char *)"+-*/^m", input_string[i])) {
      // если скобка
      if ('(' == input_string[i]) {
        // действие если откр скобка
        append(stack, '(');
      }
      if (')' == input_string[i]) {
        close_bracket_handler(stack, output);
      }
      if (is_char_in_str((char *)"+-*/^", input_string[i]) ||
          ((i + 3) < input_length && input_string[i] == 'm' &&
           input_string[i + 1] == 'o' && input_string[i + 2] == 'd')) {
        // если знак+-*/
        // действие если знак

        if (input_string[i] == 'm') {
          i += 2;
          sign_handler(stack, output, '%');
        } else {
          sign_handler(stack, output, input_string[i]);
        }
      }
    } else {
      // иначе парсим элемент
      result *= element_parsing(input_string, &i, input_length, output, stack);
    }
    i++;
  }
  reverse(stack);
  for (int i = 0; i < (int)strlen(stack); i++) {
    separator_append(output);
    append(output, stack[i]);
  }
  return result;
}

void unary_signs_normalize(char *input_str) {
  char buffer[260] = "\0";
  int buffer2[260] = {};
  if (input_str[0] == '-') {
    append(buffer, '0');
    strcat(buffer, input_str);
    strcpy(input_str, buffer);
    buffer[0] = '\0';
  }
  if (input_str[0] == '+') {
    del_sign(input_str, 0);
  }
  int input_len = strlen(input_str);
  int bracket_numbers = 0;

  for (int i = 0; i < input_len; i++) {
    if (input_str[i] == '(' && input_str[i + 1] == '+') {
      buffer2[bracket_numbers] = i + 1;
      bracket_numbers += 1;
    }
  }
  for (int i = 0; i < bracket_numbers; i++) {
    del_sign(input_str, buffer2[i] - i);
  }
  bracket_numbers = 0;
  for (int i = 0; i < input_len; i++) {
    if (input_str[i] == '(' && input_str[i + 1] == '-') {
      buffer2[bracket_numbers] = i + 1;
      bracket_numbers += 1;
    }
  }
  for (int i = 0; i < bracket_numbers; i++) {
    append_sign_to_str(input_str, '0', buffer2[i] + i);
  }
}
void append_sign_to_str(char *input_str, char sign, size_t pos) {
  char left[260] = "\0";
  char rigth[260] = "\0";
  slice_string(input_str, left, 0, pos);
  slice_string(input_str, rigth, pos, strlen(input_str));
  append(left, sign);
  strcat(left, rigth);
  strcpy(input_str, left);
}

void del_sign(char *input_str, size_t sign_number) {
  char left[260] = "\0";
  slice_string(input_str, left, 0, sign_number);
  char right[260] = "\0";
  slice_string(input_str, right, sign_number + 1, strlen(input_str));
  strcat(left, right);
  strcpy(input_str, left);
}

void reverse(char *input) {
  int len = strlen(input);
  char buffer[260] = "";
  for (int i = len - 1; i >= 0; i--) {
    buffer[len - 1 - i] = input[i];
  }
  buffer[len] = '\0';
  strcpy(input, buffer);
}

void sign_handler(char *stack, char *output, char sign) {
  int i = strlen(stack) - 1;
  if (sign == '^') {
    append(stack, sign);
  }
  if (sign == '-' || sign == '+') {
    while (i >= 0 && stack[i] != '(') {
      separator_append(output);
      append(output, stack[i]);
      stack[i] = '\0';
      i--;
    }

    append(stack, sign);
  }
  if (sign == '*' || sign == '/' || sign == '%') {
    while (i >= 0 && stack[i] != '(' &&
           (stack[i] == '*' || stack[i] == '/' || stack[i] == '%' ||
            stack[i] == '^')) {
      separator_append(output);
      append(output, stack[i]);
      stack[i] = '\0';
      i--;
    }
    append(stack, sign);
  }
}

void close_bracket_handler(char *stack, char *output) {
  int stack_length = strlen(stack);
  int i = stack_length - 1;
  while (i >= 0 && stack[i] != '(') {
    separator_append(output);
    append(output, stack[i]);
    stack[i] = '\0';
    i--;
  }
  stack[i] = '\0';
  if (is_char_in_str((char *)"sctCSTqlL", stack[i - 1])) {
    separator_append(output);
    append(output, stack[i - 1]);
    stack[i - 1] = '\0';
  }
}

int element_parsing(char *input_string, int *i, int input_length, char *output,
                    char *stack) {
  // 1 - всё норм 0 - ошибка
  int result = 1;
  char buffer[260] = "\0";
  //запускаем цикл
  int elem_type = 0;
  while (*i <= input_length && elem_type == 0) {
    //если не знак и не скобка, то складываем в баффер
    if (is_char_in_str((char *)"(+-*/^m)\0", input_string[*i]) == 0 &&
        *i < input_length) {
      //добавляем в баффер
      if (input_string[*i] != ' ') {
        append(buffer, input_string[*i]);
      }
    } else {
      //иначе выясняем тип элемента
      elem_type = get_elem_type(buffer);
      //  если без ошибок, то добавляем элемент
      if (elem_type != 3) {
        if (elem_type == 2) {
          // append(buffer, '(');
          char trig_code = get_trig_code(buffer);
          if (trig_code == '\0') {
            result = 0;
          }
          append(stack, trig_code);
        }
        if (elem_type == 1) {
          separator_append(output);
          strcat(output, buffer);
          buffer[0] = '\0';
        }
      } else {
        result = 0;
      }
    }
    *i += 1;
  }
  *i -= 2;
  return result;
}

char get_trig_code(char *buffer) {
  char out_code = '\0';
  if (strcmp(buffer, "sin") == 0) {
    out_code = 's';
  }
  if (strcmp(buffer, "cos") == 0) {
    out_code = 'c';
  }
  if (strcmp(buffer, "tan") == 0) {
    out_code = 't';
  }
  if (strcmp(buffer, "acos") == 0) {
    out_code = 'C';
  }
  if (strcmp(buffer, "asin") == 0) {
    out_code = 'S';
  }
  if (strcmp(buffer, "atan") == 0) {
    out_code = 'T';
  }
  if (strcmp(buffer, "sqrt") == 0) {
    out_code = 'q';
  }
  if (strcmp(buffer, "ln") == 0) {
    out_code = 'l';
  }
  if (strcmp(buffer, "log") == 0) {
    out_code = 'L';
  }
  return out_code;
}

void separator_append(char *output) {
  int out_strlen = strlen(output);
  if (out_strlen > 0) {
    append(output, ';');
  }
}
int get_elem_type(char *buffer) {
  // 1 - число, 2-тригонометрияб 3 - ошибка
  int result = 3;
  if (is_number(buffer)) {
    result = 1;
  }
  if (str_in_trig_arr(buffer)) {
    result = 2;
  }
  return result;
}

int is_number(char *buffer) {
  int buffer_length = strlen(buffer);
  int result = 1;
  if (buffer_length == 0) {
    result = 0;
  }
  if (strcmp("x", buffer)) {
    for (int i = 0; i < buffer_length; i++) {
      if (is_char_in_str((char *)"0123456789.", buffer[i]) == 0) {
        result = 0;
      }
    }
  }
  return result;
}

int s21_numeric_expression_validator(char *input_string) {
  int result = is_brakets_valid(input_string);
  return result;
}


int is_char_in_str(char *input_string_orig, char sign) {
  int i = 0;
  int result = 0;
  while (input_string_orig[i] != '\0' && result == 0) {
    if (input_string_orig[i] == sign) {
      result = 1;
    }
    i++;
  }
  return result;
}

int str_in_trig_arr(char *input_string_orig) {
  int trig_count = 9;
  char trig_arr[9][5] = {"sin",  "cos",  "tan", "acos", "asin",
                         "atan", "sqrt", "ln",  "log"};
  int result = 0;
  for (int i = 0; i < trig_count; i++) {
    if (strcmp(trig_arr[i], input_string_orig) == 0) {
      result = 1;
    }
  }
  return result;
}

void append(char *input_string_orig, char append_sign) {
  int input_len = strlen(input_string_orig);
  input_string_orig[input_len] = append_sign;
  input_string_orig[input_len + 1] = '\0';
}

int is_brakets_valid(char *input_string_orig) {
  if (count_c(input_string_orig, '(') != count_c(input_string_orig, ')')) {
    return 0;
  }
  char input_string[270] = "\0";
  strcpy(input_string, input_string_orig);
  int close_bracket_pos = find(input_string, ')');
  char left_part_with_full_bracket[270] = "\0";
  slice_string(input_string, left_part_with_full_bracket, 0,
               close_bracket_pos + 1);
  int open_bracket_pos = rfind(left_part_with_full_bracket, '(');
  while ((open_bracket_pos != -1 && close_bracket_pos != -1) &&
         open_bracket_pos < close_bracket_pos) {
    char rigth_part[270] = "\0";
    char left_part_without_full_bracket[270] = "\0";
    slice_string(left_part_with_full_bracket, left_part_without_full_bracket, 0,
                 open_bracket_pos);
    slice_string(input_string, rigth_part, close_bracket_pos + 1,
                 strlen(input_string));
    strcat(left_part_without_full_bracket, rigth_part);
    strcpy(input_string, left_part_without_full_bracket);
    close_bracket_pos = find(input_string, ')');
    slice_string(input_string, left_part_with_full_bracket, 0,
                 close_bracket_pos + 1);
    open_bracket_pos = rfind(left_part_with_full_bracket, '(');
  }
  close_bracket_pos = find(input_string, ')');
  close_bracket_pos = find(input_string, ')');
  int result = 1;
  if (close_bracket_pos != -1 || close_bracket_pos != -1) {
    result = 0;
  }
  return result;
}

int count_c(char *input_string_orig, char find_char) {
  int count = 0;
  int input_length = strlen(input_string_orig);
  for (int i = 0; i < input_length; i++) {
    if (input_string_orig[i] == find_char) {
      count++;
    }
  }
  return count;
}

int slice_string(char *input_string, char *out_string, int begin, int end) {
  //вырезает строку с end(включительно) до begin(не включительно)
  if (end <= begin || (begin < 0 || end < 0) ||
      begin > (int)strlen(input_string)) {
    return 0;
  }
  int result_size = end - begin;
  for (int i = 0; i < result_size; i++) {
    out_string[i] = input_string[i + begin];
  }
  out_string[result_size + 1] = '\0';
  return 1;
}

int find(char *input_string, char find_char) {
  int input_length = strlen(input_string);
  int result = -1;
  for (int i = 0; i < input_length; i++) {
    if (input_string[i] == find_char && result == -1) {
      result = i;
    }
  }
  return result;
}
int rfind(char *input_string, char find_char) {
  int input_length = strlen(input_string);
  int result = -1;
  for (int i = 0; i < input_length; i++) {
    if (input_string[i] == find_char) {
      result = i;
    }
  }
  return result;
}
