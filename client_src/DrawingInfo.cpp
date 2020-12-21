#include "DrawingInfo.h"

#include <utility>

DrawingInfo::DrawingInfo(DirectedPositionable player_pos, PlayerView view,
            std::vector<Positionable> objects,
            std::vector<DirectedPositionable> directed_objects) :
            player_pos(player_pos), objects(std::move(objects)),
            directed_objects(std::move(directed_objects)), view(view){}

DirectedPositionable DrawingInfo::getPlayerPos() {
    return this->player_pos;
}

std::vector<Positionable> DrawingInfo::getStaticObjects() {
    return this->objects;
}

std::vector<DirectedPositionable> DrawingInfo::getDirectedObjects() {
    return this->directed_objects;
}

PlayerView DrawingInfo::getCameraPlanes() {
    return this->view;
}
