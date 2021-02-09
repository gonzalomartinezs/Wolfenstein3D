#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapelement.h"
#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <string>

#define TAM_MAP_DEF 5

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), container(ITEMSIZE)
{
    ui->setupUi(this);
    this->setWindowTitle("Editor de niveles");
    this->initWidgets();
    this->initBar();
    this->connectEvents();
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
    this->itemlist->loadList(this->container);
    this->mapHandler = new MapHandler(TAM_MAP_DEF ,TAM_MAP_DEF ,this);
    this->spinX->setValue(TAM_MAP_DEF);
    this->spinY->setValue(TAM_MAP_DEF);
    mapScrollArea->setWidget(mapHandler);
    this->trashBin = new TrashBin(this->trashFrame);
}

void MainWindow::initBar(){
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAction = fileMenu->addAction(tr("&Open..."), this, &MainWindow::openFile);
    openAction->setShortcuts(QKeySequence::Open);
    QAction *exitAction = fileMenu->addAction(tr("E&xit"), qApp, &QCoreApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));

    //gameMenu->addAction(tr("&Restart"), this, &MainWindow::setupPuzzle);
    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
}

void MainWindow::connectEvents(){
   QObject::connect(this->button, &QPushButton::clicked, this, &MainWindow::resizeMap);
}

void MainWindow::resizeMap(){
    if(this->mapHandler == nullptr) return;
    delete mapHandler;
    mapHandler = new MapHandler(spinX->value(), spinY->value(), this);
    mapScrollArea->setWidget(mapHandler);
}

void MainWindow::openFile(){
    QString path = QFileDialog::getOpenFileName(this);
    if (!path.isEmpty())
        loadFile(path);
}

void MainWindow::loadFile(QString& path){

}




