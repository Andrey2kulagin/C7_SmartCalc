#ifndef DEPOSIT_FORM_H
#define DEPOSIT_FORM_H

#include <QDialog>

namespace Ui {
class deposit_form;
}

class deposit_form : public QDialog {
  Q_OBJECT

 public:
  explicit deposit_form(QWidget *parent = nullptr);
  ~deposit_form();

 private slots:
  void on_calculate_clicked();

 private:
  Ui::deposit_form *ui;
};

#endif  // DEPOSIT_FORM_H
