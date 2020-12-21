#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include "../common_src/BlockingQueue.h"
#include <SDL2/SDL.h>

class EventHandler {
private:
    BlockingQueue<int>& instructions;

public:
    // Crea un EventHandler listo para ser utlilizado.
    EventHandler(BlockingQueue<int>& instructions):instructions(instructions){}

    // Ejecuta la acción del manejo de KeyEvents
    void run(bool &quit, int &flag, const Uint8 *keys);

    // Libera los recursos utilizados por el event handler.
    ~EventHandler(){}
};


#endif //EVENTHANDLER_H
