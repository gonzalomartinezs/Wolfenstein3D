#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapelement.h"
#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QMessageBox>
#include <string>

#define ITEMSIZE 100

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    this->loadElements();
    this->itemlist = new ItemList(ITEMSIZE, items,this);
    frameLayout->addWidget(itemlist);
    frameLayout->addWidget(map);
    setCentralWidget(frame);
}


void MainWindow::loadElements(){
    Q_INIT_RESOURCE(editor);

    int i = 0;
    bool done = false;
    while(!done){
       QPixmap newImage;
       if( newImage.load( QStringLiteral(":/img/%1").arg(i) ) ){
            Item x;
            x.id = i;
            x.pixmap = newImage.scaled(ITEMSIZE, ITEMSIZE);
            items.push_back(x);
           i++;
       } else {
           done = true;
       }
    }
}

