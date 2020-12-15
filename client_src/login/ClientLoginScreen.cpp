//
// Created by riedel on 25/11/20.
//

#include <QtWidgets/QApplication>
#include "ClientLoginScreen.h"

void ClientLoginScreen::operator()() {
    char* argv = " ";
    int argc = 1;
    QApplication app(argc,&argv);
    Login login( name, port, host);
    login.show();
    app.exec();
}

const std::string &ClientLoginScreen::getName() {
    return name;
}

const std::string &ClientLoginScreen::getHost() {
    return host;
}

const std::string &ClientLoginScreen::getPort() {
    return port;
}
