//
// Created by riedel on 19/2/21.
//

#include "MessageBox.h"

MessageBox::MessageBox(QWidget *parent) : QMessageBox(parent) {

}

void MessageBox::showError(const std::string &error) {
    this->exec();
}

