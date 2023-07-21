#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow), _controller(new s21::CalculationController(new s21::CalculateModel())) {
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(s21_input_process()));

    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(s21_input_process()));

    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(s21_input_process()));

    connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(s21_input_process()));

    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(s21_input_process()));

    connect(ui->pushButton_lbracket, SIGNAL(clicked()), this, SLOT(s21_input_process()));
    connect(ui->pushButton_rbracket, SIGNAL(clicked()), this, SLOT(s21_input_process()));

    connect(ui->pushButton_del_symb, SIGNAL(clicked()), this, SLOT(s21_del_one_symbol_process()));
    connect(ui->pushButton_del_all, SIGNAL(clicked()), this, SLOT(s21_del_all_equation_process()));

    connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(s21_equal_process()));
    connect(ui->graph, SIGNAL(clicked()), this, SLOT(s21_open_graph()));
}

MainWindow::~MainWindow() {
    delete ui;

}

void MainWindow::s21_input_process() {
     QPushButton *button = (QPushButton *)sender();
     std::string lable = button->text().toLocal8Bit().data();

     _output_string = QString::fromStdString(_controller->s21_add_member(lable));

     ui->label_expression->setText(_output_string);
}

void MainWindow::s21_del_one_symbol_process() {
    _output_string = QString::fromStdString(_controller->s21_delete_member());
     ui->label_expression->setText(_output_string);
}

void MainWindow::s21_del_all_equation_process() {
    _output_string = QString::fromStdString(_controller->s21_delete_all());
     ui->label_expression->setText(_output_string);
}

void MainWindow::s21_equal_process() {
    std::string equation = _output_string.toLocal8Bit().data();

    if (_controller->s21_validate_equation()) {
        long double calculation_result = _controller->s21_calculation(equation);
        ui->label_result->setText(QString::number(calculation_result, 'g', 10));
    } else {
        ui->label_result->setText("Illegal format");
    }
    _output_string = QString::fromStdString(_controller->s21_delete_all());
}

void MainWindow::s21_open_graph() {
     QPushButton *button = (QPushButton *)sender();
    if (button->isChecked()) {
        graph.setGeometry(this->geometry().x() + this->geometry().width(), this->geometry().y(), this->geometry().width(), this->geometry().height());
        graph.show();
    } else {
        graph.close();
    }
}

void MainWindow::closeEvent(QCloseEvent* e) {
    QWidget::closeEvent(e);
    graph.close();
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
//    for (double X = -xmax; X <= xmax; X += step) {
//        x.push_back(X);
//        y.push_back((double)s21_set_graph(result, X));
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

