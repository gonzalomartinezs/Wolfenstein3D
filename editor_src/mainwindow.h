#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "itemList.h"
#include "maphandler.h"
#include "trashbin.h"
#include "iconscontainer.h"

#include <QMainWindow>
#include <vector>
#include <QScrollArea>
#include <QSpinBox>
#include <QPushButton>
#include "MessageBox.h"

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
    void saveFileAs();
    void restart();

 signals:
    void showYamlError();

 private:
    void initWidgets();
    void initBar();
    void linkToUI();
    void connectEvents();
    void loadFile(QString& path);
    Ui::MainWindow *ui;

    QScrollArea* mapScrollArea;
    QSpinBox* spinX;
    QSpinBox* spinY;
    QPushButton* button;
    QLineEdit* nameLabel;

    TrashBin* trashBin;
    ItemList* itemList;
    MapHandler* mapHandler;
    IconsContainer container;
    MessageBox notiBox;
};

#endif // MAINWINDOW_H
