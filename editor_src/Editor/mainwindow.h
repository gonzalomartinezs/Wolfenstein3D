#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "itemList.h"
#include "map.h"
#include "item.h"
#include <QMainWindow>
#include <vector>

#define ITEMSIZE 100

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
    Ui::MainWindow *ui;
    ItemList* itemlist;
    Map* map;
    std::vector<Item> items;
};

#endif // MAINWINDOW_H
