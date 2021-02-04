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
    initWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets(){
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);
    this->loadElements();
    this->itemlist = new ItemList(ITEMSIZE, items,this);
    this->map = new Map(items);
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

