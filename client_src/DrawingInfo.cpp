#include "DrawingInfo.h"

#include <utility>

DrawingInfo::DrawingInfo(DirectedPositionable player_pos, PlayerView view,
                         std::vector<int> player_info,
                         std::vector<Positionable> objects,
                         std::vector<DirectedPositionable> directed_objects) :
            player_pos(player_pos), player_info(std::move(player_info)),
            objects(std::move(objects)),
            directed_objects(std::move(directed_objects)), view(view){}


std::vector<int> DrawingInfo::getPlayerInfo() const {
    return this->player_info;
}
DirectedPositionable DrawingInfo::getPlayerPos() const {
    return this->player_pos;
}

std::vector<Positionable> DrawingInfo::getStaticObjects() const {
    return this->objects;
}

std::vector<DirectedPositionable> DrawingInfo::getDirectedObjects() const {
    return this->directed_objects;
}

PlayerView DrawingInfo::getCameraPlanes() const {
    return this->view;
}

