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
    this ->loadIcons();
    initWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets(){
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);
    this->map = new Map;
    this->list = new ItemList(100, this);
    this->loadIcons();
    frameLayout->addWidget(list);
    frameLayout->addWidget(map);
    setCentralWidget(frame);
}

void MainWindow::loadImage(QPixmap &pixmap, const QString &path){
    if (!pixmap.load(path)) {
        QMessageBox::warning(this, tr("Open Image"),
                             tr("The image file could not be loaded."),
                             QMessageBox::Close);
        return;
    }
}

void MainWindow::loadIcons(){
    Q_INIT_RESOURCE(editor);

    int i = 0;
    while(true){
        QPixmap newImage;
       if( !newImage.load( QString::number(i) ) ) break;
       list->add(newImage);
       i++;
    }
}

