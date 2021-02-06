#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "itemList.h"
#include "map.h"
#include "item.h"
#include "trashbin.h"

#include <QMainWindow>
#include <vector>
#include <QScrollArea>
#include <QSpinBox>

#define ITEMSIZE 50

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initWidgets();
    void loadElements();
    void linkToUI();
    Ui::MainWindow *ui;

    QScrollArea* mapScrollArea;
    QFrame* trashFrame;
    QSpinBox* spinX;
    QSpinBox* spinY;

    TrashBin* trashBin;
    ItemList* itemlist;
    Map* map;
};

#endif // MAINWINDOW_H
