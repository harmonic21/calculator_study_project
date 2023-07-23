#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::Graph)
{
    ui_->setupUi(this);
}

Graph::~Graph()
{
    delete ui_;
}

void Graph::PlotGraph(s21::CalculationController* controller, std::string equation) {
    double y_max = ui_->doubleSpinBoxY->value();
    double x_max = ui_->doubleSpinBoxX->value();
    double step = ui_->doubleSpinBoxStep->value();
    y_max = y_max == 0 ? 20.0 : y_max;
    x_max = x_max == 0 ? 20.0 : x_max;
    step = step == 0 ? 0.1 : step;

    for (double x = -x_max; x <= x_max; x += step) {
        x_.push_back(x);
        y_.push_back(controller->PrepareAxis(equation, x));
    }

        ui_->widget->addGraph();
        ui_->widget->graph(0)->setData(x_, y_);
        ui_->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui_->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
        ui_->widget->xAxis->setRange(-x_max, x_max);
        ui_->widget->yAxis->setRange(-y_max, y_max);
        ui_->widget->replot();
        x_.clear();
        y_.clear();

}
