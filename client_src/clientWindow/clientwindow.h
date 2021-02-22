#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QListView>
#include "StringList.h"
#include "Resolution.h"
#include "ResolutionList.h"

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
    StringList mapList;
    StringList matchList;
    ResolutionList resoList;

    void linkToUI();

    void initWidgets();

    void connectEvents();

    void gameLoop();

    QPushButton *selectMatchButton;
    QPushButton *selectMapButton;

};

#endif // CLIENTWINDOW_H
