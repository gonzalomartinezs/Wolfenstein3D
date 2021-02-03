#ifndef PROTECTEDDRAWINGINFO_H
#define PROTECTEDDRAWINGINFO_H

#include <mutex>
#include <vector>
#include "PlayerView.h"
#include "../common_src/Positionable.h"
#include "../common_src/SlidingSurface.h"
#include "../common_src/DirectedPositionable.h"

class DrawingInfo {
private:
    DirectedPositionable player_pos;
    PlayerView view;
    std::vector<int> player_info;
    std::vector<Positionable> objects;
    std::vector<DirectedPositionable> directed_objects;
    std::vector<std::pair<int,int>> sliders_changes;

public:
    // Crea un DrawingInfo listo para ser utilizado.
    DrawingInfo(DirectedPositionable player_pos, PlayerView view,
                std::vector<int> player_info, std::vector<Positionable> objects,
                std::vector<DirectedPositionable> directed_objects,
                std::vector<std::pair<int,int>> sliders_changes);

    // Retorna un arreglo con los valores de vidas, hp, balas,... del jugador.
    std::vector<int> getPlayerInfo() const;
    // Retorna la posicion del jugador.
    DirectedPositionable getPlayerPos() const;
    // Retorna un vector con los objetos estaticos en el mapa.
    std::vector<Positionable> getStaticObjects() const;
    // Retorna un vector con los objetos dinamicos en el mapa.
    std::vector<DirectedPositionable> getDirectedObjects() const;
    // Retorna el plano camara del jugador.
    PlayerView getCameraPlanes() const;
    // Retorna un arreglo con pares de los cambios en las puertas y pasadizos
    // (id, nuevo_estado)
    std::vector<std::pair<int,int>> getSlidersChanges() const;

    ~DrawingInfo(){}
};


#endif //PROTECTEDDRAWINGINFO_H
