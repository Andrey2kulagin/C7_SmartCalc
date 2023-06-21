#ifndef CHART_H
#define CHART_H

#include <QDialog>
#include <QVector>

namespace Ui {
class Chart;
}

class Chart : public QDialog {
  Q_OBJECT

 public:
  explicit Chart(QWidget *parent = nullptr);
  ~Chart();

 private:
  Ui::Chart *ui;
  double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;
 public slots:
  void slot(QString a);
 private slots:
  void on_recalc_clicked();
};

#endif  // CHART_H
