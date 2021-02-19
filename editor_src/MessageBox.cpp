//
// Created by riedel on 19/2/21.
//

#include "MessageBox.h"

MessageBox::MessageBox(QWidget *parent) : QMessageBox(parent) {

}

void MessageBox::showMessage (const std::string &msg) {
    this->exec();
}

