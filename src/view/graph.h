#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

#include "Qcustomplot/qcustomplot.h"

#include "../controller/calculation_controller.h"

namespace Ui {
    class Graph;
}

class Graph : public QWidget {
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);

    ~Graph();

    void PlotGraph(s21::CalculationController* controller, std::string equation);

private:
    Ui::Graph *ui_;

    QVector<double> x_;

    QVector<double> y_;

};

#endif // GRAPH_H
