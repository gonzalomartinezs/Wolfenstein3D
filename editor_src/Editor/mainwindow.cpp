#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapelement.h"
#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QMessageBox>
#include <string>

#define TAM_MAP_DEF 5

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
    this->spinX = findChild<QSpinBox*>("spinX");
    this->spinY = findChild<QSpinBox*>("spinY");
    this->button = findChild<QPushButton*>("button");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets(){
    this->linkToUI();
    this->map = new Map(TAM_MAP_DEF ,TAM_MAP_DEF ,this);
    this->spinX->setValue(TAM_MAP_DEF);
    this->spinY->setValue(TAM_MAP_DEF);
    mapScrollArea->setWidget(map);
    this->trashBin = new TrashBin(this->trashFrame);
}

void MainWindow::connectEvents(){
    QObject::connect(q)
}


