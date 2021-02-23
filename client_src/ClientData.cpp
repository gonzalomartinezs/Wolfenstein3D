#include "ClientData.h"
#include "../common_src/GameConstants.h"

ClientData::ClientData(SDL_Renderer *renderer, SDL_Surface *surface,
                       Map &map, Resolution &resolution,
                       ProtectedQueue<UI_Info> &drawing_info,
                       BlockingQueue<int> &instructions,
                       UI_Info initial_info) :
                       map(map),
                       tex(renderer, surface), sounds(),
                       raycaster(map, resolution.getX() / 32,
                                 (-resolution.getY()) / 18,
                                 (30 * resolution.getX()) / 32,
                                 (17 * resolution.getY()) / 18, tex),
                       event_handler(instructions),
                       sound_handler(sounds, map),
                       ui_handler(renderer, raycaster, tex,
                                  "../client_src/fonts/Vermin Vibes 1989.ttf",
                                  resolution.getX(), resolution.getY()),
                       game_interface(ui_handler, sound_handler,
                                      drawing_info, initial_info, REFRESH_RATE){
}

GameInterface &ClientData::getGameInterface() {
    return this->game_interface;
}

EventHandler &ClientData::getEventHandler() {
    return this->event_handler;
}

ClientData::~ClientData() {}
