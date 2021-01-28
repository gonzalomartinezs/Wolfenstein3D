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
    this ->loadIcons();
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


void MainWindow::loadIcons(){
    Q_INIT_RESOURCE(editor);

    int i = 0;
    bool done = false;
    while(!done){
        QPixmap newImage;
       printf("una iteracion");
       if( newImage.load( QStringLiteral(":/img/%1").arg(i) ) ){
          list->add(newImage);
           i++;
       } else {
           done = true;
       }
    }
}

