#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapelement.h"
#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <string>
#include <list>

#include "mapparser.h"
#include "mapelement.h"


#define TAM_MAP_DEF 5

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), container(ITEMSIZE) {
    ui->setupUi(this);
    this->setWindowTitle("Editor de niveles");
    this->initWidgets();
    this->initBar();
    this->connectEvents();
}

void MainWindow::linkToUI() {
    this->itemlist = findChild<ItemList*>("itemList");
    this->mapScrollArea = findChild<QScrollArea*>("mapArea");
    this->trashFrame = findChild<QFrame*>("trashFrame");
    this->spinX = findChild<QSpinBox*>("spinX");
    this->spinY = findChild<QSpinBox*>("spinY");
    this->button = findChild<QPushButton*>("button");
    this->nameLabel = findChild <QLineEdit*>("nameLabel");
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initWidgets() {
    this->linkToUI();
    this->itemlist->loadList(this->container);
    this->mapHandler = new MapHandler(this->container,"-",TAM_MAP_DEF ,TAM_MAP_DEF ,this);
    this->spinX->setValue(TAM_MAP_DEF);
    this->spinY->setValue(TAM_MAP_DEF);
    mapScrollArea->setWidget(mapHandler);
    this->trashBin = new TrashBin(this->trashFrame);
}

void MainWindow::initBar() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAction = fileMenu->addAction(tr("&Open..."), this, &MainWindow::openFile);
    openAction->setShortcuts(QKeySequence::Open);

    QAction *saveAsAction = fileMenu->addAction(tr("&Save as..."), this, &MainWindow::saveFile);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);

    QAction *exitAction = fileMenu->addAction(tr("E&xit"), qApp, &QCoreApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(tr("&Restart"), this, &MainWindow::resizeMap);
    QMenu* helpMenu = menuBar()->addMenu( tr("&Help") );
    helpMenu->addAction( (tr(("&instructions"))) );
}

void MainWindow::connectEvents() {
   QObject::connect(this->button, &QPushButton::clicked, this, &MainWindow::resizeMap);
}

void MainWindow::resizeMap() {
    if(this->mapHandler == nullptr) return;

    std::list<MapElement> elements = mapHandler->getMap().getElements();
    delete mapHandler;
    mapHandler = new MapHandler(container,nameLabel->text().toStdString()
                                ,spinX->value(), spinY->value(), this);
    mapHandler->loadElements(elements);
    mapScrollArea->setWidget(mapHandler);
}

void MainWindow::openFile() {
    QString path = QFileDialog::getOpenFileName(this);
    if ( !path.isEmpty() ) {
        loadFile(path);
    }
}

void MainWindow::loadFile(QString& path) {
    parser.loadMap( );
}

void MainWindow::saveFile(){
    parser.exportMap(mapHandler->getMap() );
}
