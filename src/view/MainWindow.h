#ifndef SRC_SMARTCALC_MAINWINDOW_H_
#define SRC_SMARTCALC_MAINWINDOW_H_

#include "../controller/CalculationController.h"


#include <QMainWindow>
#include "graph.h"
#include <QVector>

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; } QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  virtual void closeEvent(QCloseEvent* e);

  ~MainWindow();

private:
 Ui::MainWindow *ui;
 Graph graph;
 s21::CalculationController* _controller;
 QString _output_string;
 QVector<double> _x;
 QVector<double> _y;

private slots:

 void s21_input_process();
 void s21_del_one_symbol_process();
 void s21_del_all_equation_process();
 void s21_equal_process();
 void s21_open_graph();


 // void PlotGraph(char* result);
};



#endif  //  SRC_SMARTCALC_CALCULATION_VIEW_H_
