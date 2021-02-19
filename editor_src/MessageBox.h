//
// Created by riedel on 19/2/21.
//
#include <QMessageBox>
#include <string>

#ifndef EDITOR_MESSAGEBOX_H
#define EDITOR_MESSAGEBOX_H


class MessageBox : public QMessageBox {
    Q_OBJECT
public:
    explicit MessageBox(QWidget* parent = nullptr);
public slots:
    void showYamlError();
    void showOccupiedPosition();
};


#endif //EDITOR_MESSAGEBOX_H
