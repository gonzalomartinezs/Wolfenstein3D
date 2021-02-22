#ifndef RAYCASTINGTHREAD_H
#define RAYCASTINGTHREAD_H

#include <atomic>
#include "../client_src/UI_Info.h"
#include "../common_src/Thread.h"
#include "../common_src/ProtectedQueue.h"
#include "../common_src/Positionable.h"
#include "../common_src/DirectedPositionable.h"
#include "../client_src/UI_Handler.h"
#include "../client_src/SoundHandler.h"

class GameInterface: public Thread {
private:
    UI_Handler& ui_handler;
    SoundHandler& sound_handler;
    ProtectedQueue<UI_Info>& queue;
    UI_Info latest_info;
    int refresh_rate;
    std::atomic<bool> keep_running;

public:
    // Crea una interfaz de juego lista para ser utilizada.
    GameInterface(UI_Handler& ui_handler, SoundHandler& sound_handler,
                  ProtectedQueue<UI_Info>& queue,
                  UI_Info initial_info, int refresh_rate);

    // Realiza el renderizado entre 2 transiciones la cantidad de veces
    // indicada en refresh rate.
    void run() override;

    // Detiene la ejecución del hilo.
    void stop() override;

    // Retorna un bool que indica si se finalizo el proceso o no.
    bool finished() override;

    // Muestra el leaderboard del juego por pantalla.
    void showLeaderboard(std::vector<std::string> &names,
                         std::vector<int> &values);

    ~GameInterface();

private:
    void _updateScreen(UI_Info new_info);
};

#endif //RAYCASTINGTHREAD_H
