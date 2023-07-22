#include "main_window.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui_(new Ui::MainWindow), controller_(new s21::CalculationController(new s21::CalculateModel())) {
    ui_->setupUi(this);
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

    connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(InputProcess()));

    connect(ui_->pushButton_lbracket, SIGNAL(clicked()), this, SLOT(InputProcess()));
    connect(ui_->pushButton_rbracket, SIGNAL(clicked()), this, SLOT(InputProcess()));

    connect(ui_->pushButton_del_symb, SIGNAL(clicked()), this, SLOT(DelOneSymbolProcess()));
    connect(ui_->pushButton_del_all, SIGNAL(clicked()), this, SLOT(DelAllEquationProcess()));

    connect(ui_->pushButton_equal, SIGNAL(clicked()), this, SLOT(EqualProcess()));
    connect(ui_->graph, SIGNAL(clicked()), this, SLOT(OpenGraph()));
}

MainWindow::~MainWindow() {
    delete ui_;
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
}

void MainWindow::EqualProcess() {
    std::string equation = output_string_.toLocal8Bit().data();

    if (controller_->ValidateEquation()) {
        long double calculation_result = controller_->Calculation(equation);
        ui_->label_result->setText(QString::number(calculation_result, 'g', 10));
    } else {
        ui_->label_result->setText("Illegal format");
    }
    output_string_ = QString::fromStdString(controller_->DeleteAll());
}

void MainWindow::OpenGraph() {
     QPushButton *button = (QPushButton *)sender();
    if (button->isChecked()) {
        graph_.setGeometry(this->geometry().x() + this->geometry().width(), this->geometry().y(), this->geometry().width(), this->geometry().height());
        graph_.show();
    } else {
        graph_.close();
    }
}

void MainWindow::closeEvent(QCloseEvent* e) {
    QWidget::closeEvent(e);
    graph_.close();
}




//void CalculationView::PlotGraph(char* result) {
//    double ymax = ui->doubleSpinBox_ymax->value();
//    double xmax = ui->doubleSpinBox_xmax->value();
//    double step = ui->doubleSpinBox_x->value();
//    if (ymax == 0) {
//        ymax = 20.0;
//    }
//    if (xmax == 0) {
//        xmax = 20.0;
//    }
//    if (step == 0) {
//        step = 0.01;
//    }
//    for (double kX = -xmax; kX <= xmax; kX += step) {
//        x.push_back(kX);
//        y.push_back((double)s21_set_graph(result, kX));
//    }
//    ui->widget->addGraph();
//    ui->widget->graph(0)->setData(x, y);
//    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
//    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
//    ui->widget->xAxis->setRange(-xmax, xmax);
//    ui->widget->yAxis->setRange(-ymax, ymax);
//    ui->widget->replot();
//    x.clear();
//    y.clear();
//}

