#include <QWidget>
#include <QHBoxLayout>
#include <QFileDialog>
#include <list>

#include "InvalidFileException.h"
#include "mapparser.h"
#include "mapelement.h"
#include "MessageBox.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#define TAM_MAP_DEF 13

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      container(ITEMSIZE) {
    ui->setupUi(this);
    this->setWindowTitle("Editor De Niveles");
    this->initWidgets();
    this->initBar();
    this->connectEvents();
}

void MainWindow::initWidgets() {
    this->linkToUI();
    this->itemList->loadList(this->container);
    this->mapHandler = new MapHandler(this->container,"-",TAM_MAP_DEF ,TAM_MAP_DEF ,this);
    this->spinX->setValue(TAM_MAP_DEF);
    this->spinY->setValue(TAM_MAP_DEF);
    this->nameLabel->setPlaceholderText("Name of the map");
    mapScrollArea->setWidget(mapHandler);
}

void MainWindow::linkToUI() {
    this->itemList = findChild<ItemList*>("itemList");
    this->mapScrollArea = findChild<QScrollArea*>("mapArea");
    this->trashBin = findChild<TrashBin*>("trashBin");
    this->spinX = findChild<QSpinBox*>("spinX");
    this->spinY = findChild<QSpinBox*>("spinY");
    this->button = findChild<QPushButton*>("button");
    this->nameLabel = findChild <QLineEdit*>("nameLabel");
}

void MainWindow::initBar() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAction = fileMenu->addAction(tr("&Open..."), this, &MainWindow::openFile);
    openAction->setShortcuts(QKeySequence::Open);

    QAction *saveAsAction = fileMenu->addAction(tr("&Save as..."), this, &MainWindow::saveFileAs);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);

    QAction *exitAction = fileMenu->addAction(tr("E&xit"), qApp, &QCoreApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(tr("&Restart"), this, &MainWindow::restart);
    QMenu* helpMenu = menuBar()->addMenu( tr("&Help") );
    helpMenu->addAction( (tr(("&instructions"))) );
}

void MainWindow::connectEvents() {
   QObject::connect(this->button, &QPushButton::clicked, this, &MainWindow::resizeMap);
   QObject::connect(this, &MainWindow::showYamlError,
                    &notiBox, &MessageBox::showYamlError);

   QObject::connect(this->mapHandler, &MapHandler::showOccupiedPosition,
                    &notiBox, &MessageBox::showOccupiedPosition);
}

void MainWindow::resizeMap() {
    mapHandler->resizeMap( spinX->value(), spinY->value(),
                           nameLabel->text().toStdString());
}

void MainWindow::openFile() {
    QString path = QFileDialog::getOpenFileName(this);
    if ( !path.isEmpty() ) {
        loadFile(path);
    }
}

void MainWindow::loadFile(QString& path) {
    MapParser parser;
    Map map;
    try {
        map = parser.loadMap( path.toStdString() );
    }catch (InvalidFileException &e){
            emit showYamlError();
            return;
    }
    if(this->mapHandler == nullptr) return;
    delete mapHandler; mapHandler = nullptr;
    spinX->setValue( map.getX() );
    spinY->setValue( map.getY() );
    nameLabel->setText( map.getName().c_str() );
    std::list<MapElement> elements = map.getElements();
    mapHandler =  new MapHandler (container,
                                  nameLabel->text().toStdString()
                                    ,map.getX(), map.getY(), this );
    mapHandler->loadElements(elements);
    mapScrollArea->setWidget(mapHandler);
}

void MainWindow::saveFileAs() {
    MapParser parser;
    QString path = QFileDialog::getSaveFileName(this);
    if ( !path.isEmpty() ) {
        parser.exportMap(mapHandler->getMap(), path.toStdString() );
    }
}

void MainWindow::restart() {
    if(this->mapHandler == nullptr) return;
    delete mapHandler;
    spinX->setValue(TAM_MAP_DEF);
    spinY->setValue(TAM_MAP_DEF);
    nameLabel->clear();
    mapHandler = new MapHandler(container,nameLabel->text().toStdString()
            ,spinX->value(), spinY->value(), this);
    mapScrollArea->setWidget(mapHandler);
}

MainWindow::~MainWindow() {
    delete ui;
    delete mapHandler;
}
