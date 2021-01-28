#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "itemList.h"
#include "map.h"
#include "mapelement.h"
#include <QMainWindow>
#include <vector>

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
    void loadIcons();
    Ui::MainWindow *ui;
    ItemList* itemlist;
    Map* map;
    std::vector<MapElement> elements;
};

#endif // MAINWINDOW_H
