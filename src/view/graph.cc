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
