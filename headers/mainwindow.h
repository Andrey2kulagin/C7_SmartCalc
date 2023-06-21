#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <chart.h>

#include <QMainWindow>

#include "credit.h"
#include "deposit_form.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_minus_button_clicked();

  void on_clear_button_clicked();

  void on_mod_button_clicked();

  void on_pow_button_clicked();

  void on_sqrt_button_clicked();

  void on_ln_button_clicked();

  void on_log_button_clicked();

  void on_acos_button_clicked();

  void on_asin_button_clicked();

  void on_atan_button_clicked();

  void on_sin_button_clicked();

  void on_cos_button_clicked();

  void on_tan_button_clicked();

  void on_seven_button_clicked();

  void on_eigth_button_clicked();

  void on_nine_button_clicked();

  void on_four_button_clicked();

  void on_five_button_clicked();

  void on_six_button_clicked();

  void on_one_button_clicked();

  void on_two_button_clicked();

  void on_three_button_clicked();

  void on_open_bracket_button_clicked();

  void on_close_bracket_button_clicked();

  void on_null_button_clicked();

  void on_point_button_clicked();

  void on_backspace_button_clicked();

  void on_div_button_clicked();

  void on_mult_button_clicked();

  void on_plus_button_clicked();

  void on_equally_button_clicked();

  void on_pushButton_2_clicked();

  void on_credit_button_clicked();

  void on_depos_button_clicked();

 private:
  Ui::MainWindow *ui;
  Chart *chart;
  deposit_form deposit_form;
  credit credit;
 signals:
  void signal(QString);
};

#endif  // MAINWINDOW_H
