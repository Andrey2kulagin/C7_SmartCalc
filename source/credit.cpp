#include "../headers/credit.h"

#include <QStandardItemModel>

#include "../headers/c_libs.h"
#include "ui_credit.h"
credit::credit(QWidget *parent) : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);
}
/*struct credit_input {
    double credit_in_sum; //общая сумма double
    int loan_term;  // срок int
    double interest_rate; // процентная ставка double
    int loan_type; // тип int
};*/

credit::~credit() { delete ui; }

void credit::on_pushButton_clicked() {
  ui->loan_type->setStyleSheet("");
  ui->credit_in_sum->setStyleSheet("");
  ui->loan_term->setStyleSheet("");
  ui->interest_rate->setStyleSheet("");
  QString credit_in_sum_qs = ui->credit_in_sum->text();
  QString loan_term_qs = ui->loan_term->text();
  QString interest_rate_qs = ui->interest_rate->text();
  bool loan_type_1 = ui->loan_type_1->isChecked();
  bool loan_type_2 = ui->loan_type_2->isChecked();
  bool is_all_validate = true;
  int loan_type = 0;
  if (loan_type_1) {
    loan_type = 1;
  } else {
    if (loan_type_2) {
      loan_type = 2;
    } else {
      ui->loan_type->setStyleSheet("background-color: red");
      is_all_validate = false;
    }
  }
  bool is_value_valid = false;
  double credit_in_sum_double = credit_in_sum_qs.toDouble(&is_value_valid);
  if (is_value_valid == false || credit_in_sum_qs.isEmpty()) {
    ui->credit_in_sum->setStyleSheet("background-color: red");
    is_all_validate = false;
  }
  int loan_term = loan_term_qs.toInt(&is_value_valid);
  if (is_value_valid == false || loan_term_qs.isEmpty()) {
    ui->loan_term->setStyleSheet("background-color: red");
    is_all_validate = false;
  }
  double interest_rate = interest_rate_qs.toDouble(&is_value_valid);
  if (is_value_valid == false || interest_rate_qs.isEmpty()) {
    ui->interest_rate->setStyleSheet("background-color: red");
    is_all_validate = false;
  }
  if (is_all_validate) {
    struct credit_input input;
    struct credit_output output;
    input.credit_in_sum = credit_in_sum_double;
    input.loan_term = loan_term;
    input.interest_rate = interest_rate;
    input.loan_type = loan_type;
    s21_credit_calc(input, &output);
    if (loan_type_1) {
      ui->month_payment->setText(output.month_payment);
      ui->over_payment->setText(output.over_payment);
      ui->total_payout->setText(output.total_payment);
    } else {
      ui->over_payment->setText(output.over_payment);
      ui->total_payout->setText(output.total_payment);
      QStandardItemModel *model = new QStandardItemModel(this);
      model->setColumnCount(1);  // Устанавливаем количество колонок
      model->setRowCount(output.diff_payments_count +
                         1);  // Устанавливаем количество строк
      // Заполняем модель данными
      for (int i = 0; i < output.diff_payments_count + 1; i++) {
        if (i == 0) {
          QModelIndex index = model->index(i, 0, QModelIndex());
          model->setData(index,
                         QString("вся выплата | проценты | тело кредита"));
        } else {
          QModelIndex index = model->index(i, 0, QModelIndex());
          model->setData(index, QString(output.diff_payments[i - 1]));
        }
      }
      ui->listView->setModel(model);
      ui->listView->setViewMode(
          QListView::ListMode);  // Устанавливаем режим отображения списка
      ui->listView->setWrapping(false);  // Отключаем перенос строк
      ui->listView->setVerticalScrollMode(
          QAbstractItemView::ScrollPerPixel);  // Устанавливаем режим скроллинга
    }
  }
}
/*
struct credit_input {
  double credit_in_sum; //общая сумма double
  int loan_term;        // срок int
  double interest_rate; // процентная ставка double
  int loan_type;        // тип int
};

struct credit_output {
  char month_payment[280];       //месячная плата double
  char over_payment[280];        // переплата double
  char total_payment[280];       // общая выплата double
  char diff_payments[1024][280]; // список строк для диффиренцированного платежа
};*/
