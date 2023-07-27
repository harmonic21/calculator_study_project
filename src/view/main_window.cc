#include "main_window.h"

#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      controller_(new s21::CalculationController(new s21::CalculateModel())) {
  ui_->setupUi(this);
  setWindowTitle("Calculator (╮°-°)╮┳━━┳ ");
  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(InputProcess()));

  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_sub, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_sum, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_mul, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_del, SIGNAL(clicked()), this, SLOT(InputProcess()));

  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(InputProcess()));

  connect(ui_->pushButton_X, SIGNAL(clicked()), this, SLOT(InputProcess()));
  connect(ui_->pushButton_E, SIGNAL(clicked()), this, SLOT(InputProcess()));

  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(InputProcess()));

  connect(ui_->pushButton_lbracket, SIGNAL(clicked()), this,
          SLOT(InputProcess()));
  connect(ui_->pushButton_rbracket, SIGNAL(clicked()), this,
          SLOT(InputProcess()));

  connect(ui_->pushButton_del_symb, SIGNAL(clicked()), this,
          SLOT(DelOneSymbolProcess()));
  connect(ui_->pushButton_del_all, SIGNAL(clicked()), this,
          SLOT(DelAllEquationProcess()));

  connect(ui_->pushButton_equal, SIGNAL(clicked()), this, SLOT(EqualProcess()));
  connect(ui_->graph, SIGNAL(clicked()), this, SLOT(GraphProcess()));
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::closeEvent(QCloseEvent *e) {
  QWidget::closeEvent(e);
  graph_.close();
}

void MainWindow::InputProcess() {
  QPushButton *button = (QPushButton *)sender();
  std::string lable = button->text().toLocal8Bit().data();

  output_string_ = QString::fromStdString(controller_->AddMember(lable));

  ui_->label_expression->setText(output_string_);
}

void MainWindow::DelOneSymbolProcess() {
  output_string_ = QString::fromStdString(controller_->DeleteMember());
  ui_->label_expression->setText(output_string_);
}

void MainWindow::DelAllEquationProcess() {
  output_string_ = QString::fromStdString(controller_->DeleteAll());
  ui_->label_expression->setText(output_string_);
  graph_.ClearGraph();
}

void MainWindow::EqualProcess() {
  std::string equation = output_string_.toLocal8Bit().data();

  if (controller_->ValidateEquation()) {
    if (equation.find("X") != std::string::npos) {
      OpenGraph();
      graph_.PlotGraph(controller_, equation);
    } else {
      long double calculation_result = controller_->Calculation(equation);
      ui_->label_result->setText(QString::number(calculation_result, 'g', 10));
    }
  } else {
    ui_->label_result->setText("Illegal format");
  }
  ui_->label_expression->clear();
  output_string_ = QString::fromStdString(controller_->DeleteAll());
}

void MainWindow::GraphProcess() {
  QPushButton *button = (QPushButton *)sender();
  if (button->isChecked()) {
    OpenGraph();
  } else {
    graph_.close();
  }
}

void MainWindow::OpenGraph() {
  int X = this->geometry().x();
  int Y = this->geometry().y();
  int width = this->geometry().width();
  int height = this->geometry().height();
  graph_.setGeometry(X + width, Y, width, height);
  graph_.ScaleGraph();
  graph_.show();
}
