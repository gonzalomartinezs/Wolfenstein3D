//
// Created by riedel on 19/2/21.
//
#include <QMessageBox>
#ifndef EDITOR_MESSAGEBOX_H
#define EDITOR_MESSAGEBOX_H


class MessageBox : public QMessageBox {
    Q_OBJECT
public:
    explicit MessageBox(QWidget* parent = nullptr);
public slots:
    void showErrorOnFile();
    void showCoordinateOccupied();
};


#endif //EDITOR_MESSAGEBOX_H
