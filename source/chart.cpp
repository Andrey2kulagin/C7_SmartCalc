#include "../headers/chart.h"

#include "../headers/c_libs.h"
#include "ui_chart.h"
Chart::Chart(QWidget *parent) : QDialog(parent), ui(new Ui::Chart) {
  ui->setupUi(this);
}

Chart::~Chart() { delete ui; }

void Chart::slot(QString func_name) {
  ui->widget->xAxis->setRange(-100, 100);
  ui->widget->yAxis->setRange(-100, 100);
  ui->func_name_label->setText(func_name);

  QVector<double> x, y;
  for (long int i = -10; i <= 10; i += 1) {
    double result_value = 0;
    char input[1024] = "\0";
    QByteArray input_bytes = func_name.toUtf8();
    std::strcpy(input, input_bytes.constData());
    char x_value[260] = "\0";
    sprintf(x_value, "%ld", i);
    int result_code = s21_calculator_to_chart(input, &result_value, x_value);
    if (result_code) {
      printf("%lf\n", result_value);
      x.push_back(i);
      y.push_back(result_value);
    } else {
      x.push_back(i);
      y.push_back(std::numeric_limits<double>::quiet_NaN());
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->replot();
}

void Chart::on_recalc_clicked() {
  QString max_x_edit_text = ui->max_x_edit->text();
  QString min_x_edit_text = ui->min_x_edit->text();
  QString step_text = ui->step->text();
  QString max_x_edit_2_text = ui->max_x_edit_2->text();
  QString min_x_edit_2_text = ui->min_x_edit_2->text();
  QString max_y_edit_2_text = ui->max_y_edit_2->text();
  QString min_y_edit_2_text = ui->min_y_edit_2->text();
  bool all_is_int = true;
  // Конвертируем в число
  bool max_x_edit_is_integer = false;
  long int max_x_edit_number = max_x_edit_text.toInt(&max_x_edit_is_integer);
  if (max_x_edit_is_integer == false) {
    ui->max_x_edit->setStyleSheet("background-color: red");
    all_is_int = false;
  } else {
    ui->max_x_edit->setStyleSheet("");
  }

  bool min_x_edit_is_integer = false;
  long int min_x_edit_number = min_x_edit_text.toInt(&min_x_edit_is_integer);
  if (min_x_edit_is_integer == false) {
    ui->min_x_edit->setStyleSheet("background-color: red");
    all_is_int = false;
  } else {
    ui->min_x_edit->setStyleSheet("");
  }

  bool step_text_is_double = false;
  double step_number = step_text.toDouble(&step_text_is_double);
  if (step_text_is_double == false) {
    ui->step->setStyleSheet("background-color: red");
    all_is_int = false;
  } else {
    ui->step->setStyleSheet("");
  }

  bool max_x_edit_is_integer_2 = false;
  long int max_x_edit_number_2 =
      max_x_edit_2_text.toInt(&max_x_edit_is_integer_2);
  if (max_x_edit_is_integer_2 == false) {
    ui->max_x_edit_2->setStyleSheet("background-color: red");
    all_is_int = false;
  } else {
    ui->max_x_edit_2->setStyleSheet("");
  }

  bool min_x_edit_is_integer_2 = false;
  long int min_x_edit_number_2 =
      min_x_edit_2_text.toFloat(&min_x_edit_is_integer_2);
  if (min_x_edit_is_integer_2 == false) {
    ui->min_x_edit_2->setStyleSheet("background-color: red");
    all_is_int = false;
  } else {
    ui->min_x_edit_2->setStyleSheet("");
  }

  bool max_y_edit_is_integer_2 = false;
  long int max_y_edit_number_2 =
      max_y_edit_2_text.toInt(&max_y_edit_is_integer_2);
  if (max_y_edit_is_integer_2 == false) {
    ui->max_y_edit_2->setStyleSheet("background-color: red");
    all_is_int = false;
  } else {
    ui->max_y_edit_2->setStyleSheet("");
  }

  bool min_y_edit_is_integer_2 = false;
  long int min_y_edit_number_2 =
      min_y_edit_2_text.toInt(&min_y_edit_is_integer_2);
  if (min_y_edit_is_integer_2 == false) {
    ui->min_y_edit_2->setStyleSheet("background-color: red");
    all_is_int = false;
  } else {
    ui->min_y_edit_2->setStyleSheet("");
  }
  if (step_number < 0 or
      step_number > (abs(min_x_edit_number) + abs(max_x_edit_number))) {
    ui->step->setStyleSheet("background-color: red");
    all_is_int = false;
  } else {
    ui->step->setStyleSheet("");
  }

  if (all_is_int == true) {
    ui->widget->xAxis->setRange(min_x_edit_number_2, max_x_edit_number_2);
    ui->widget->yAxis->setRange(min_y_edit_number_2, max_y_edit_number_2);
    QString func_name = ui->func_name_label->text();
    QVector<double> x, y;
    for (double i = min_x_edit_number; i <= max_x_edit_number;
         i += step_number) {
      double result_value = 0;
      char input[1024] = "\0";
      QByteArray input_bytes = func_name.toUtf8();
      std::strcpy(input, input_bytes.constData());
      char x_value[260] = "\0";
      sprintf(x_value, "%lf", i);
      printf("%lf\n", i);

      int result_code = s21_calculator_to_chart(input, &result_value, x_value);
      if (fabs(i - 0.0) <= 0.00001) {
        printf("asjkhasd");
      }
      if (result_code) {
        printf("%lf\n", result_value);
        x.push_back(i);
        y.push_back(result_value);
      }
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    ui->widget->replot();
  }
}
