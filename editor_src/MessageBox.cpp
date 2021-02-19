//
// Created by riedel on 19/2/21.
//

#include "MessageBox.h"

MessageBox::MessageBox(QWidget *parent) : QMessageBox(parent) {
    this->setText( "-" );

}

void MessageBox::showYamlError() {
    this->setText( "Formato de archivo invalido" );
    this->exec();
}

void MessageBox::showOccupiedPosition() {
    this->setText( "Posicion Ocupada" );
    this->exec();
}


