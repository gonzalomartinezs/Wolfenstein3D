//
// Created by riedel on 25/11/20.
//

#ifndef QTPLAYGROUND_LOGIN_H
#define QTPLAYGROUND_LOGIN_H


#include <QWidget>
#include <QtMultimedia/QAudioOutput>


class Login : public QWidget {
 private:
    void getArguments();
    void connectEvents();
    std::string& name;
    std::string& port;
    std::string& host;
 public:
    Login(std::string& name, std::string &port, std::string& host);
    std::string& getName();
    std::string& getPort();
    std::string& getHost();
};


#endif //QTPLAYGROUND_LOGIN_H
