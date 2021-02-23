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

QT_BEGIN_NAMESPACE // Magia de Qt.
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Ventana Principal de Qt.
class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

 private slots:
    // Cambia el tam del mapa segun los valores de los spinbox de la ventana.
    void resizeMap();
    // Abre ventana que permite seleccionar que archivo abrir.
    void openFile();
    //Abre ventana que permite selecionar un archivo donde guardar el mapa.
    void saveFileAs();
    // Reinicia el Editor.
    void restart();

 signals:
    // Emite senal indicando cuando no se pudo abrir un archivo.
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
