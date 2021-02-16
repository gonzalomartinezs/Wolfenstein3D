#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "itemList.h"
#include "maphandler.h"
#include "trashbin.h"
#include "iconscontainer.h"
#include "mapparser.h"

#include <QMainWindow>
#include <vector>
#include <QScrollArea>
#include <QSpinBox>
#include <QPushButton>

#define ITEMSIZE 50

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void resizeMap();
    void openFile();
    void saveFile();

private:
    void initWidgets();
    void initBar();
    void loadElements();
    void linkToUI();
    void connectEvents();
    void loadFile(QString& path);
    Ui::MainWindow *ui;

    QScrollArea* mapScrollArea;
    QFrame* trashFrame;
    QSpinBox* spinX;
    QSpinBox* spinY;
    QPushButton* button;
    QLineEdit* nameLabel;

    TrashBin* trashBin;
    ItemList* itemlist;
    MapHandler* mapHandler;
    IconsContainer container;
    MapParser parser;
};

#endif // MAINWINDOW_H
