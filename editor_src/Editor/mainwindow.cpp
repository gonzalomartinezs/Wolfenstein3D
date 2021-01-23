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
    puzzleWidget = new PuzzleWidget(400);

    piecesList = new PiecesList(puzzleWidget->pieceSize(), this);


    connect(puzzleWidget, &PuzzleWidget::puzzleCompleted,
            this, &MainWindow::setCompleted, Qt::QueuedConnection);

    frameLayout->addWidget(piecesList);
    frameLayout->addWidget(puzzleWidget);
    setCentralWidget(frame);
}

