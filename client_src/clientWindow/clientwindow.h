#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QListView>
#include <QSpinBox>
#include "StringList.h"
#include "Resolution.h"
#include "ResolutionList.h"

#include "../Client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWindow; }
QT_END_NAMESPACE

class ClientWindow : public QMainWindow {
    Q_OBJECT

public:
    ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void connectToServer();
    void joinMatchMenu();
    void createMatchMenu();
    void createMatch();
    void joinMatch();

private:
    Ui::ClientWindow *ui;
    QWidget* loginPage;
    QWidget* optionPage;
    QWidget* newGamePage;
    QWidget* joinGamePage;
    QStackedWidget* stack;
    QPushButton *loginButton;
    QPushButton *optionjoinButton;
    QPushButton *optionCreateButton;
    QLineEdit*  name;
    QLineEdit*  host;
    QSpinBox*   port;
    StringList mapList;
    StringList matchList;
    ResolutionList resoList;
    Resolution resolution;

    Client* client;
    ProtectedQueue<UI_Info> drawing_info;
    BlockingQueue<int> instructions;


    void linkToUI();
    void initWidgets();
    void connectEvents();
    void gameLoop();
    QPushButton *selectMatchButton;
    QPushButton *selectMapButton;

};

#endif // CLIENTWINDOW_H
