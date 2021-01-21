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
    std::vector<int> player_info;
    std::vector<Positionable> objects;
    std::vector<DirectedPositionable> directed_objects;

public:
    // Crea un DrawingInfo listo para ser utilizado.
    DrawingInfo(DirectedPositionable player_pos, PlayerView view,
                std::vector<int> player_info, std::vector<Positionable> objects,
                std::vector<DirectedPositionable> directed_objects);

    std::vector<int> getPlayerInfo() const;
    DirectedPositionable getPlayerPos() const;
    std::vector<Positionable> getStaticObjects() const;
    std::vector<DirectedPositionable> getDirectedObjects() const;
    PlayerView getCameraPlanes() const;

    // Libera los recursos utilzados por el objecto.
    ~DrawingInfo(){}
};


#endif //PROTECTEDDRAWINGINFO_H
