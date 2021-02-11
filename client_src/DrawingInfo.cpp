#include "DrawingInfo.h"

#include <utility>

DrawingInfo::DrawingInfo(DirectedPositionable player_pos, PlayerView view,
                         std::vector<int> player_info,
                         std::vector<Positionable> objects,
                         std::vector<DirectedPositionable> directed_objects,
                         std::vector<std::pair<int,int>> sliders_changes) :
            player_pos(player_pos), player_info(std::move(player_info)),
            objects(std::move(objects)), sliders_changes(sliders_changes),
            directed_objects(std::move(directed_objects)), view(view) {}

// Todo esto tiene que recibir y devolver copias de vectores?
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

std::vector<std::pair<int, int>> DrawingInfo::getSlidersChanges() const {
    return this->sliders_changes;
}

