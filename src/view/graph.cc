#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget* parent) : QWidget(parent), ui_(new Ui::Graph) {
  ui_->setupUi(this);
  setWindowTitle("Plot ( ╯°□°)╯ ┻━━┻");
}

Graph::~Graph() {
  delete ui_;
  x_.clear();
  y_.clear();
}

void Graph::PlotGraph(s21::CalculationController* controller,
                      std::string equation) {
  double y_max = ui_->YButton->value();
  double x_max = ui_->XButton->value();
  double step = ui_->StepButton->value();
  y_max = y_max == 0 ? 20.0 : y_max;
  x_max = x_max == 0 ? 20.0 : x_max;
  step = step == 0 ? 0.1 : step;

  for (double x = -x_max; x <= x_max; x += step) {
    x_.push_back(x);
    y_.push_back(controller->PrepareAxis(equation, x));
  }
  PaintGraph(x_max, y_max);
  x_.clear();
  y_.clear();
}

void Graph::ScaleGraph() {
  ui_->widget->setGeometry(0, 0, this->geometry().width(),
                           this->geometry().height());
  ui_->widget->setInteraction(QCP::iRangeZoom, true);
  ui_->widget->setInteraction(QCP::iRangeDrag, true);
  ui_->widget->axisRect()->setRangeDrag(Qt::Horizontal);
  ui_->widget->axisRect()->setRangeZoom(Qt::Horizontal);
}

void Graph::ClearGraph() {
  x_.clear();
  y_.clear();
  ui_->widget->clearGraphs();
  ui_->widget->replot();
}

void Graph::PaintGraph(double x_max, double y_max) {
  ui_->widget->addGraph();
  ui_->widget->graph(0)->setData(x_, y_);
  ui_->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui_->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
  ui_->widget->xAxis->setRange(-x_max, x_max);
  ui_->widget->yAxis->setRange(-y_max, y_max);
  ui_->widget->replot();
}
