#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initWidgets(){
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);
    this->map = new Map;
    this->list = new ItemList;

    frameLayout->addWidget(list);
    frameLayout->addWidget(map);
    setCentralWidget(frame);
}

