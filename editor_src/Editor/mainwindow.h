#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "itemList.h"
#include "map.h"
#include "mapelement.h"
#include <QMainWindow>
#include <vector>

#define MAX_ITEMS 4

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
    void loadImage(QPixmap &pixmap, const QString &path);
    Ui::MainWindow *ui;
    ItemList* list;
    Map* map;
    MapElement elements [MAX_ITEMS];
};

#endif // MAINWINDOW_H
