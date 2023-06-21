#include "../headers/deposit_form.h"

#include "../headers/c_libs.h"
#include "ui_deposit_form.h"
deposit_form::deposit_form(QWidget *parent)
    : QDialog(parent), ui(new Ui::deposit_form) {
  ui->setupUi(this);
}

deposit_form::~deposit_form() { delete ui; }

void deposit_form::on_calculate_clicked() {
  ui->deposit_initial_sum->setStyleSheet("");
  ui->placement_period->setStyleSheet("");
  ui->income_rate->setStyleSheet("");
  ui->tax->setStyleSheet("");
  ui->frequency_of_payments->setStyleSheet("");
  ui->is_capitalization->setStyleSheet("");
  ui->replanishment->setStyleSheet("");
  ui->replanishment_sum->setStyleSheet("");
  ui->partial_repleneshment->setStyleSheet("");
  ui->partial_withdrawal_sum->setStyleSheet("");

  QString deposit_initial_sum_qs = ui->deposit_initial_sum->text();
  QString placement_period_qs = ui->placement_period->text();
  QString income_rate_qs = ui->income_rate->text();
  QString tax_rate_qs = ui->tax->text();
  int frequency_of_payments = ui->frequency_of_payments->currentIndex();
  bool is_capitalization = ui->is_capitalization->isChecked();
  int replanishment_type = ui->replanishment->currentIndex();
  QString replanishment_sum_qs = ui->partial_repleneshment->text();
  int partial_withdrawal_type = ui->partial_withdrawal->currentIndex();
  QString partial_withdrawal_sum_qs = ui->partial_withdrawal_sum->text();
  bool is_all_validate = true;

  bool is_value_valid = false;
  double deposit_initial_sum = deposit_initial_sum_qs.toDouble(&is_value_valid);
  if (is_value_valid == false || deposit_initial_sum_qs.isEmpty()) {
    ui->deposit_initial_sum->setStyleSheet("background-color: red");
    is_all_validate = false;
  }
  int placement_period = placement_period_qs.toInt(&is_value_valid);
  if (is_value_valid == false || placement_period_qs.isEmpty()) {
    ui->placement_period->setStyleSheet("background-color: red");
    is_all_validate = false;
  }
  double tax_rate = tax_rate_qs.toDouble(&is_value_valid);
  if (is_value_valid == false || tax_rate_qs.isEmpty()) {
    ui->tax->setStyleSheet("background-color: red");
    is_all_validate = false;
  }
  double income_rate = income_rate_qs.toDouble(&is_value_valid);
  if (is_value_valid == false || income_rate_qs.isEmpty()) {
    ui->income_rate->setStyleSheet("background-color: red");
    is_all_validate = false;
  }
  double replanishment_sum = 0;
  if (replanishment_type != 0) {
    replanishment_sum = replanishment_sum_qs.toDouble(&is_value_valid);
    if (is_value_valid == false || replanishment_sum_qs.isEmpty()) {
      ui->partial_repleneshment->setStyleSheet("background-color: red");
      is_all_validate = false;
    }
  }
  double partial_withdrawal_sum = 0;
  if (partial_withdrawal_type != 0) {
    partial_withdrawal_sum =
        partial_withdrawal_sum_qs.toDouble(&is_value_valid);
    if (is_value_valid == false || partial_withdrawal_sum_qs.isEmpty()) {
      ui->partial_withdrawal_sum->setStyleSheet("background-color: red");
      is_all_validate = false;
    }
  }
  if (is_all_validate) {
    struct deposit_input input;
    input.deposit_initial_sum = deposit_initial_sum;
    input.placement_period = placement_period;
    input.income_rate = income_rate;
    input.tax_rate = tax_rate;
    input.frequency_of_payments = frequency_of_payments;
    input.is_capitalization = is_capitalization;
    input.replanishment_type = replanishment_type;
    input.replanishment_sum = replanishment_sum;
    input.partial_withdrawal_type = partial_withdrawal_type;
    input.partial_withdrawal_sum = partial_withdrawal_sum;
    struct deposit_output output;
    int result_code = s21_deposit_calc(input, &output);

    /*
struct deposit_output {
char accured_interest[280]; // начисленные проценты double
char tax_sum[280];          // сумма налога double
char anount_of_account[280]; //сумма на вкладе на конец double
};
*/
    if (result_code) {
      ui->accured_interest->setText(output.accured_interest);
      ui->tax_sum->setText(output.tax_sum);
      ui->anount_of_account->setText(output.anount_of_account);
    } else {
      ui->partial_withdrawal_sum->setStyleSheet("background-color: red");
      ui->partial_repleneshment->setStyleSheet("background-color: red");
      ui->income_rate->setStyleSheet("background-color: red");
      ui->tax->setStyleSheet("background-color: red");
      ui->placement_period->setStyleSheet("background-color: red");
      ui->deposit_initial_sum->setStyleSheet("background-color: red");
    }
  }
}
