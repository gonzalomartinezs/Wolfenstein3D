#ifndef PROTECTEDDRAWINGINFO_H
#define PROTECTEDDRAWINGINFO_H

#include <mutex>
#include <vector>
#include "PlayerView.h"
#include "../common_src/Positionable.h"
#include "../common_src/SlidingSurface.h"
#include "../common_src/DirectedPositionable.h"

class UI_Info {
private:
    DirectedPositionable player_pos;
    PlayerView view;
    std::vector<int> player_info;
    std::vector<Positionable> objects;
    std::vector<DirectedPositionable> directed_objects;
    std::vector<int> doors_states;
    std::vector<std::pair<int,float>> sounds;
    bool important;

public:
    // Crea un UI_Info listo para ser utilizado.
    UI_Info(DirectedPositionable player_pos, PlayerView view,
            std::vector<int> player_info, std::vector<Positionable> objects,
            std::vector<DirectedPositionable> directed_objects,
            std::vector<int> doors_states,
            std::vector<std::pair<int,float>> sounds, bool important);

    // Retorna un arreglo con los valores de vidas, hp, balas,... del jugador.
    std::vector<int>& getPlayerInfo();
    // Retorna la posicion del jugador.
    DirectedPositionable& getPlayerPos();
    // Retorna un vector con los objetos estaticos en el mapa.
    std::vector<Positionable>& getStaticObjects();
    // Retorna un vector con los objetos dinamicos en el mapa.
    std::vector<DirectedPositionable>& getDirectedObjects();
    // Retorna el plano camara del jugador.
    PlayerView& getCameraPlanes();
    // Retorna un arreglo con pares de estados de puertas y pasadizos (id, estado)
    std::vector<int> & getDoorStates();
    // Retorna un arreglo con pares de sonidos y distancias al jugador (id, dist)
    std::vector<std::pair<int,float>>& getSounds();
    // Retorna un booleano indicando si el paqeute es importante o no.
    bool isImportant() const;

    ~UI_Info(){}
};


#endif //PROTECTEDDRAWINGINFO_H
