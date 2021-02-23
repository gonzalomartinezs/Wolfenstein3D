#include "MessageBox.h"

MessageBox::MessageBox(QWidget *parent) : QMessageBox(parent) {
    this->setText( "-" );
}

void MessageBox::showYamlError() {
    this->setText( "Formato de archivo invalido" );
    this->exec();
}

void MessageBox::showInstructions() {
    this->setText( "Editor de Niveles de Wolfestein 3D, "
                   "para ver usos leer el manual de usuario" );
    this->exec();
}