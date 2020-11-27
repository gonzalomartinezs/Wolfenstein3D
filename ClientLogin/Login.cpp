//
// Created by riedel on 25/11/20.
//

#include "Login.h"
#include "ui_Login.h"

Login::Login(std::string& name, std::string &port, std::string& host) :
                                                        name(name),
                                                        port(port),
                                                        host(host){
    Ui::Login login;
    login.setupUi(this);
    connectEvents();  //  cargo en this la configuracion del uic.
}

void Login::getArguments() {
    QLineEdit* input = findChild<QLineEdit*>("inputName");
    this->name = input->text().toStdString();
    input = findChild<QLineEdit*>("inputHost");
    this->host = input->text().toStdString();
    input = findChild<QLineEdit*>("inputPort");
    this->port = input->text().toStdString();
    this->close();
}

void Login::connectEvents() {
    QPushButton* connectButton = findChild<QPushButton*>
                                    ("connectButton");
    QObject::connect(connectButton, &QPushButton::clicked,
                     this, &Login::getArguments);
}


