#ifndef SRC_SMARTCALC_MAINWINDOW_H_
#define SRC_SMARTCALC_MAINWINDOW_H_

#include <QMainWindow>
#include <QVector>

#include "../controller/calculation_controller.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    virtual void closeEvent(QCloseEvent *e);

    ~MainWindow();

private:
    Ui::MainWindow *ui_;
    Graph graph_;
    s21::CalculationController *controller_;
    QString output_string_;

private slots:
    void InputProcess();

    void DelOneSymbolProcess();

    void DelAllEquationProcess();

    void EqualProcess();

    void OpenGraph();


    // void PlotGraph(char* result);
};


#endif  //  SRC_SMARTCALC_CALCULATION_VIEW_H_
