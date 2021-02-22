#include <iostream>
#include "clientwindow.h"
#include "./ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Wolfenstein 3D");
    this->linkToUI();
    this->initWidgets();
    this->connectEvents();
}


void ClientWindow::linkToUI() {
    loginPage = findChild<QWidget*>("loginPage");
    optionPage = findChild<QWidget*>("optionPage");
    newGamePage = findChild<QWidget*>("newGamePage");
    joinGamePage = findChild<QWidget*>("joinGamePage");
    stack = findChild<QStackedWidget*>("stack");
    loginButton = findChild<QPushButton*>("loginButton");
    optionjoinButton = findChild<QPushButton*>("connectToMatchButton");
    optionCreateButton = findChild<QPushButton*>("createMatchButton");
    selectMapButton = findChild<QPushButton*>("selectMapButton");
    selectMatchButton = findChild<QPushButton*>("selectMatchButton");
    QWidget* aux = findChild<QWidget*>("frameMaps");
    mapList.setParent(aux);
    aux = findChild<QWidget*>("frameMatchs");
    matchList.setParent(aux);
}


void ClientWindow::initWidgets() {
    stack->setCurrentWidget(loginPage);
    for (int i = 0; i < 20; ++i) {
        matchList.addItem(i,"xd");
    }
}

void ClientWindow::connectEvents() {
    connect (loginButton, &QPushButton::clicked,
             this, &ClientWindow::connectToServer);
    connect (optionjoinButton, &QPushButton::clicked,
             this, &ClientWindow::joinMatchMenu);
    connect (optionCreateButton, &QPushButton::clicked,
             this, &ClientWindow::createMatchMenu);
    connect (selectMatchButton, &QPushButton::clicked,
             this, &ClientWindow::gameLoop);
    connect (selectMapButton, &QPushButton::clicked,
             this, &ClientWindow::gameLoop );
}

ClientWindow::~ClientWindow() {
    delete ui;
}

void ClientWindow::connectToServer() {
    //hacer la logica si se puede conectar o no, si no puede deberia tirar cartel.

    stack->setCurrentWidget(optionPage);
}

void ClientWindow::joinMatchMenu() {
    resoList.setParent(findChild<QWidget*>("resolutionWidget_2"));
    stack->setCurrentWidget(joinGamePage);

}

void ClientWindow::createMatchMenu() {
    resoList.setParent(findChild<QWidget*>("resolutionWidget_1"));
    stack->setCurrentWidget(newGamePage);
}

void ClientWindow::gameLoop() {
    printf("hola jorge");
    std::cout << int  (matchList.getSelected() );
}

void ClientWindow::createMatch() {

}

void ClientWindow::joinMatch() {

}