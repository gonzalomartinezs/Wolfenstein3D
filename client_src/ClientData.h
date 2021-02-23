#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include "Raycaster.h"
#include "UI_Handler.h"
#include "EventHandler.h"
#include "SoundHandler.h"
#include "GameInterface.h"
#include "../common_src/Map.h"
#include "sound/SoundsContainer.h"
#include "textures/TexturesContainer.h"
#include "clientWindow/Resolution.h"

class ClientData {
private:
    Map& map;
    TexturesContainer tex;
    SoundsContainer sounds;
    Raycaster raycaster;
    SoundHandler sound_handler;
    EventHandler event_handler;
    UI_Handler ui_handler;
    GameInterface game_interface;

public:
    // Crea un contenedor de la data del cliente listo para ser utilizado.
    ClientData(SDL_Renderer *renderer, SDL_Surface *surface,
               Map &map, Resolution &resolution,
               ProtectedQueue<UI_Info> &drawing_info,
               BlockingQueue<int> &instructions,
               UI_Info initial_info);

    // Retorna una referencia al GameInterface.
    GameInterface& getGameInterface();

    // Retorna una referencia al EventHandler.
    EventHandler& getEventHandler();

    // Libera los recursos utilizados por el objeto.
    ~ClientData();
};

#endif //CLIENTDATA_H
