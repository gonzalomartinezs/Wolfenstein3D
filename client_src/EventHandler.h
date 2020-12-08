#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include "Client.h"
#include <SDL2/SDL.h>

class EventHandler {
private:
    Client& client;

public:
    // Crea un EventHandler listo para ser utlilizado.
    EventHandler(Client& client): client(client){}

    // Ejecuta la acción del manejo de KeyEvents
    void run(bool &quit, int &flag, const Uint8 *keys);

    // Libera los recursos utilizados por el event handler.
    ~EventHandler(){}
};


#endif //EVENTHANDLER_H
