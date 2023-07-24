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

    void ScaleGraph();

    void ClearGraph();

private:
    Ui::Graph *ui_;

    QVector<double> x_;

    QVector<double> y_;

    void PaintGraph(double x_max, double y_max);

};

#endif // GRAPH_H
