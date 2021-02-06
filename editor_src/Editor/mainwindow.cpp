#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapelement.h"
#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QMessageBox>
#include <string>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Editor de niveles");
    initWidgets();
}

void MainWindow::linkToUI(){
    this->itemlist = findChild<ItemList*>("itemList");
    this->mapScrollArea = findChild<QScrollArea*>("mapArea");
    this->trashFrame = findChild<QFrame*>("trashFrame");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets(){
    this->linkToUI();
    this->map = new Map();
    mapScrollArea->setWidget(map);
    this->trashBin = new TrashBin(this->trashFrame);
}


