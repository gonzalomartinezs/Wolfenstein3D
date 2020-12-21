#ifndef PROTECTEDDRAWINGINFO_H
#define PROTECTEDDRAWINGINFO_H

#include <mutex>
#include <vector>
#include "PlayerView.h"
#include "../common_src/DirectedPositionable.h"
#include "../common_src/Positionable.h"


class DrawingInfo {
private:
    DirectedPositionable player_pos;
    PlayerView view;
    std::vector<Positionable> objects;
    std::vector<DirectedPositionable> directed_objects;

public:
    // Crea un DrawingInfo listo para ser utilizado.
    DrawingInfo(DirectedPositionable player_pos, PlayerView view,
                std::vector<Positionable> objects,
                std::vector<DirectedPositionable> directed_objects);

    DirectedPositionable getPlayerPos();
    std::vector<Positionable> getStaticObjects();
    std::vector<DirectedPositionable> getDirectedObjects();
    PlayerView getCameraPlanes();

    // Libera los recursos utilzados por el objecto.
    ~DrawingInfo(){}
};


#endif //PROTECTEDDRAWINGINFO_H
