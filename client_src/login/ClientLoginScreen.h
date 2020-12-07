//
// Created by riedel on 25/11/20.
//

#ifndef QTPLAYGROUND_CLIENTLOGINSCREEN_H
#define QTPLAYGROUND_CLIENTLOGINSCREEN_H


#include <string>
#include "Login.h"

class ClientLoginScreen {
 private:
    std::string name;
    std::string host;
    std::string port;
 public:
    void operator()();
    const std::string& getName();
    const std::string& getHost();
    const std::string& getPort();
};


#endif //QTPLAYGROUND_CLIENTLOGINSCREEN_H
