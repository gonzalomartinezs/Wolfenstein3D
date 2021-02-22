#include <iostream>
#include "clientwindow.h"
#include "./ui_clientwindow.h"
#include "../Window.h"
#include "../EventHandler.h"


#define REFRESH_RATE 10
#define IS_NOT_MOVING 0
const double TICK_DURATION = 1/256.f;

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow) {
    ui->setupUi(this);
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
    stack = findChild<QStackedWidget*>("stack");
    name = findChild<QLineEdit*>("name");
    host = findChild<QLineEdit*>("host");
    port = findChild<QSpinBox*>("port");
    loginButton = findChild<QPushButton*>("loginButton");
    optionjoinButton = findChild<QPushButton*>("connectToMatchButton");
    optionCreateButton = findChild<QPushButton*>("createMatchButton");
    selectMapButton = findChild<QPushButton*>("selectMapButton");
    selectMatchButton = findChild<QPushButton*>("selectMatchButton");
    QWidget* aux = findChild<QWidget*>("frameMaps");
    mapList.setParent(aux);
    aux = findChild<QWidget*>("frameMatchs");
    matchList.setParent(aux);
}


void ClientWindow::initWidgets() {
    stack->setCurrentWidget(loginPage);
    for (int i = 0; i < 20; ++i) {
        matchList.addItem(i,"xd");
    }
}

void ClientWindow::connectEvents() {
    connect (loginButton, &QPushButton::clicked,
             this, &ClientWindow::connectToServer);
    connect (optionjoinButton, &QPushButton::clicked,
             this, &ClientWindow::joinMatchMenu);
    connect (optionCreateButton, &QPushButton::clicked,
             this, &ClientWindow::createMatchMenu);
    connect (selectMatchButton, &QPushButton::clicked,
             this, &ClientWindow::gameLoop);
    connect (selectMapButton, &QPushButton::clicked,
             this, &ClientWindow::gameLoop );
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
    resolution = resoList.getSelected();
    this->client->sendMapChoice(mapList.getSelected() );
    this->gameLoop();
}

void ClientWindow::joinMatch() {
    resolution = resoList.getSelected();
    this->client->sendMatchChoice(matchList.getSelected() );
    this->gameLoop();
}

void ClientWindow::gameLoop() {
    Window window("Wolfenstein 3D", resolution.getX(), resolution.getY(),
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  SDL_WINDOW_SHOWN);
    TexturesContainer tex(window.getRenderer(), window.getSurface());
    SoundsContainer sounds;
    Map map(client->receiveMap());
    EventHandler event_handler(instructions);
    Raycaster raycaster(map, resolution.getX() / 32, (-resolution.getY()) / 18,
                        (30 * resolution.getX()) / 32, (17 * resolution.getY()) / 18,
                        tex);
    UI_Handler ui_handler(window.getRenderer(), raycaster, tex,
                          "../client_src/fonts/Vermin Vibes 1989.ttf",
                          resolution.getX(), resolution.getY());
    SoundHandler sound_handler(sounds, map);

    DirectedPositionable player(2, 2, -1, 0, None);
    PlayerView view(0,1);
    std::vector<Positionable> static_objects;
    std::vector<DirectedPositionable> directed_objects;
    std::vector<int> door_states;
    std::vector<std::pair<int,float>> game_sounds;

    UI_Info initial_info(player, view, std::vector<int>(7, 0),
                         static_objects, directed_objects, door_states,
                         false, game_sounds, false);
    GameInterface game_interface(ui_handler, sound_handler, drawing_info, initial_info, REFRESH_RATE);

    int flag = IS_NOT_MOVING;
    Timer time_between_updates;
    double last_tick_time;

    std::thread send_thread(&Client::sendInstruction, client);
    std::thread recv_thread(&Client::receiveInformation, client);

    game_interface.start();

    bool quit = false;
    while (!quit && client->isPlaying()) {
        time_between_updates.start();
        const Uint8 *keys = SDL_GetKeyboardState(NULL);

        event_handler.run(quit, flag, keys);
        last_tick_time = time_between_updates.getTime();
        if (last_tick_time < TICK_DURATION*1000) {
            usleep((TICK_DURATION * 1000 - last_tick_time) * 1000);
        }
    }
    if (quit) client->stopInGameInteraction();

    game_interface.stop();
    game_interface.join();
    send_thread.join();
    recv_thread.join();

    if (!quit) client->loadLeaderboard(game_interface);
    SDL_Event event;
    while(!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
    client->shutdown();
}