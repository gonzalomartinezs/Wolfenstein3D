#include <iostream>
#include "clientwindow.h"
#include "./ui_clientwindow.h"
#include "../Window.h"
#include "../EventHandler.h"
#include "../ClientData.h"
#include "../../common_src/GameConstants.h"
#include "../InstructionLooper.h"


ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow) {
    ui->setupUi(this);
    QPixmap bkgnd("../client_src/clientWindow/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    this->setWindowTitle("Wolfenstein 3D");
    this->linkToUI();
    this->initWidgets();
    this->connectEvents();
}


void ClientWindow::linkToUI() {
    loginPage = findChild<QWidget*>("loginPage");
    optionPage = findChild<QWidget*>("optionPage");
    newGamePage = findChild<QWidget*>("newGamePage");
    joinGamePage = findChild<QWidget*>("joinGamePage");
    inGamePage  = findChild<QWidget*>("inGamePage");
    wantToJoin =  findChild<QWidget*>("wantToJoin");
    stack = findChild<QStackedWidget*>("stack");
    name = findChild<QLineEdit*>("name");
    host = findChild<QLineEdit*>("host");
    port = findChild<QSpinBox*>("port");
    loginButton = findChild<QPushButton*>("loginButton");
    optionjoinButton = findChild<QPushButton*>("connectToMatchButton");
    optionCreateButton = findChild<QPushButton*>("createMatchButton");
    selectMapButton = findChild<QPushButton*>("selectMapButton");
    selectMatchButton = findChild<QPushButton*>("selectMatchButton");
    playButton = findChild<QPushButton*>("Play");
    QWidget* aux = findChild<QWidget*>("frameMaps");
    mapList.setParent(aux);
    aux = findChild<QWidget*>("frameMatchs");
    matchList.setParent(aux);
}


void ClientWindow::initWidgets() {
    stack->setCurrentWidget(loginPage);
}

void ClientWindow::connectEvents() {
    connect (loginButton, &QPushButton::clicked,
             this, &ClientWindow::connectToServer);
    connect (optionjoinButton, &QPushButton::clicked,
             this, &ClientWindow::joinMatchMenu);
    connect (optionCreateButton, &QPushButton::clicked,
             this, &ClientWindow::createMatchMenu);
    connect (selectMatchButton, &QPushButton::clicked,
             this, &ClientWindow::joinMatch);
    connect (selectMapButton, &QPushButton::clicked,
             this, &ClientWindow::createMatch );
    connect (playButton, &QPushButton::clicked,
             this, &ClientWindow::joinCreated );
}

ClientWindow::~ClientWindow() {
    delete ui;
    delete client;
}

void ClientWindow::connectToServer() {
  client = new Client(host->text().toStdString(),
                        std::to_string(port->value() ),
                        instructions, drawing_info);
    client->sendName( name->text().toStdString() );
    stack->setCurrentWidget(optionPage);
}

void ClientWindow::joinMatchMenu() {
    client->sendJoinGameChoice();
    resoList.setParent(findChild<QWidget*>("resolutionWidget_2"));
    client->getGames(matchList);
    stack->setCurrentWidget(joinGamePage);
}

void ClientWindow::createMatchMenu() {
    client->sendNewGameChoice();
    resoList.setParent(findChild<QWidget*>("resolutionWidget_1"));
    client->getMaps(mapList);
    stack->setCurrentWidget(newGamePage);
}

void ClientWindow::createMatch() {
    stack->setCurrentWidget(inGamePage);
    resolution = resoList.getSelected();
    this->client->sendMapChoice(mapList.getSelected() );
    this->stack->setCurrentWidget(wantToJoin);
}

void ClientWindow::joinMatch() {
    stack->setCurrentWidget(inGamePage);
    resolution = resoList.getSelected();
    this->client->sendMatchChoice(matchList.getSelected() );
    this->gameLoop();
}

void ClientWindow::gameLoop() {
    Map map(client->receiveMap());
    Window window("Wolfenstein 3D", resolution.getX(), resolution.getY(),
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  SDL_WINDOW_SHOWN);

    DirectedPositionable player(2, 2, -1, 0, None);
    PlayerView view(0,1);
    std::vector<Positionable> static_objects;
    std::vector<DirectedPositionable> directed_objects;
    std::vector<int> door_states;
    std::vector<int> player_hud(HUD_DATA, 0);
    std::vector<std::pair<int,float>> game_sounds;

    UI_Info initial_info(player, view, player_hud, static_objects,
                         directed_objects, door_states, game_sounds,
                         false, false);

    ClientData data(window.getRenderer(), window.getSurface(), map, resolution,
               drawing_info, instructions, initial_info);

    GameInterface& game_interface = data.getGameInterface();
    EventHandler& event_handler = data.getEventHandler();
    InstructionLooper instruction_looper(client, event_handler);
    bool player_quited = false;

    std::thread send_thread(&Client::sendInstruction, client);
    std::thread recv_thread(&Client::receiveInformation, client);

    game_interface.start();

    instruction_looper.run(player_quited);

    game_interface.stop();
    game_interface.join();
    send_thread.join();
    recv_thread.join();

    if (!player_quited) client->loadLeaderboard(game_interface);

    window.waitForClose();
    client->shutdown();
    this->close();
}

void ClientWindow::joinCreated() {
    client->sendPlay();
    this->gameLoop();
}
