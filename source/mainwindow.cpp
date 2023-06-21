#include "../headers/mainwindow.h"

#include <QDebug>
#include <QTextEdit>

#include "../headers/chart.h"
#include "../source/c_libs.c"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_credit_button_clicked() { credit.show(); }

void MainWindow::on_depos_button_clicked() { deposit_form.show(); }

void MainWindow::on_equally_button_clicked() {
  QString text = ui->textEdit->toPlainText();
  QString x_value_str = ui->x_value->text();
  bool x_value_is_int = false;
  double max_x_edit_number = x_value_str.toDouble(&x_value_is_int);
  if (x_value_is_int == false && !x_value_str.isEmpty()) {
    ui->x_value->setStyleSheet("background-color: red");
  } else {
    ui->x_value->setStyleSheet("");
    ui->textEdit->setStyleSheet("");
    char input_str[1024] = "\0";
    char out_str[290] = "\0";
    char x_value_c_string[260] = "\0";

    QByteArray input_bytes = text.toUtf8();
    std::strcpy(input_str, input_bytes.constData());

    input_bytes = x_value_str.toUtf8();
    std::strcpy(x_value_c_string, input_bytes.constData());

    if (is_char_in_str(input_str, 'x')) {
      if (!x_value_str.isEmpty()) {
        int result_code =
            s21_calculator_with_x(input_str, out_str, x_value_c_string);
        if (result_code == 0) {
          ui->textEdit->setStyleSheet("background-color: red");
        } else {
          ui->textEdit->setText(QString(out_str));
        }
      } else {
        chart = new Chart;
        chart->show();
        connect(this, &MainWindow::signal, chart, &Chart::slot);
        emit signal(text);
      }
    } else {
      int result_code = s21_calculator(input_str, out_str);
      if (result_code == 0) {
        ui->textEdit->setStyleSheet("background-color: red");
      } else {
        ui->textEdit->setText(QString(out_str));
      }
    }
  }
}

void MainWindow::on_minus_button_clicked() {
  ui->textEdit->insertPlainText("-");
}

void MainWindow::on_clear_button_clicked() { ui->textEdit->setPlainText(""); }

void MainWindow::on_mod_button_clicked() {
  ui->textEdit->insertPlainText("mod");
}

void MainWindow::on_pow_button_clicked() { ui->textEdit->insertPlainText("^"); }

void MainWindow::on_sqrt_button_clicked() {
  ui->textEdit->insertPlainText("sqrt(");
}

void MainWindow::on_ln_button_clicked() {
  ui->textEdit->insertPlainText("ln(");
}

void MainWindow::on_log_button_clicked() {
  ui->textEdit->insertPlainText("log(");
}

void MainWindow::on_acos_button_clicked() {
  ui->textEdit->insertPlainText("acos(");
}

void MainWindow::on_asin_button_clicked() {
  ui->textEdit->insertPlainText("asin(");
}

void MainWindow::on_atan_button_clicked() {
  ui->textEdit->insertPlainText("atan(");
}

void MainWindow::on_sin_button_clicked() {
  ui->textEdit->insertPlainText("sin(");
}

void MainWindow::on_cos_button_clicked() {
  ui->textEdit->insertPlainText("cos(");
}

void MainWindow::on_tan_button_clicked() {
  ui->textEdit->insertPlainText("tan(");
}

void MainWindow::on_seven_button_clicked() {
  ui->textEdit->insertPlainText("7");
}

void MainWindow::on_eigth_button_clicked() {
  ui->textEdit->insertPlainText("8");
}

void MainWindow::on_nine_button_clicked() {
  ui->textEdit->insertPlainText("9");
}

void MainWindow::on_four_button_clicked() {
  ui->textEdit->insertPlainText("4");
}

void MainWindow::on_five_button_clicked() {
  ui->textEdit->insertPlainText("5");
}

void MainWindow::on_six_button_clicked() { ui->textEdit->insertPlainText("6"); }

void MainWindow::on_one_button_clicked() { ui->textEdit->insertPlainText("1"); }

void MainWindow::on_two_button_clicked() { ui->textEdit->insertPlainText("2"); }

void MainWindow::on_three_button_clicked() {
  ui->textEdit->insertPlainText("3");
}

void MainWindow::on_open_bracket_button_clicked() {
  ui->textEdit->insertPlainText("(");
}

void MainWindow::on_close_bracket_button_clicked() {
  ui->textEdit->insertPlainText(")");
}

void MainWindow::on_null_button_clicked() {
  ui->textEdit->insertPlainText("0");
}

void MainWindow::on_point_button_clicked() {
  ui->textEdit->insertPlainText(".");
}

void MainWindow::on_backspace_button_clicked() {
  QString text = ui->textEdit->toPlainText();
  text.chop(1);
  ui->textEdit->clear();
  ui->textEdit->insertPlainText(text);
}

void MainWindow::on_div_button_clicked() { ui->textEdit->insertPlainText("/"); }

void MainWindow::on_mult_button_clicked() {
  ui->textEdit->insertPlainText("*");
}

void MainWindow::on_plus_button_clicked() {
  ui->textEdit->insertPlainText("+");
}

void MainWindow::on_pushButton_2_clicked() {
  ui->textEdit->insertPlainText("x");
}
