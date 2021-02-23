#include "InstructionLooper.h"
#include <unistd.h>

#define IS_NOT_MOVING 0
const double TICK_DURATION = 1/256.f;  /* miliseconds que tarda en actualizarse el juego */

InstructionLooper::InstructionLooper(Client *client,
                                     EventHandler &event_handler):
                                       client(client),
                                       event_handler(event_handler){
}

void InstructionLooper::run(bool &quit) {
    int flag = IS_NOT_MOVING;
    Timer time_between_updates;
    double last_tick_time;

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
}

InstructionLooper::~InstructionLooper() {}


