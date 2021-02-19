//
// Created by riedel on 19/2/21.
//

#include "MessageBox.h"

MessageBox::MessageBox(QWidget *parent) : QMessageBox(parent) {


}

void MessageBox::showMessage (std::string msg) {
    this->setText( "gonza te amo" );
    this->exec();
}

