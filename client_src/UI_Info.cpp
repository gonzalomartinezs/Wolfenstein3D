#include "UI_Info.h"

#include <utility>

UI_Info::UI_Info(DirectedPositionable player_pos, PlayerView view,
                 std::vector<int> player_info,
                 std::vector<Positionable> objects,
                 std::vector<DirectedPositionable> directed_objects,
                 std::vector<std::pair<int, int>> sliders,
                 std::vector<std::pair<int,float>> sounds, bool important) :
            player_pos(player_pos), player_info(std::move(player_info)),
            objects(std::move(objects)), sliders(std::move(sliders)),
            directed_objects(std::move(directed_objects)), view(view),
            sounds(std::move(sounds)), important(important){}


std::vector<int>& UI_Info::getPlayerInfo() {
    return this->player_info;
}
DirectedPositionable& UI_Info::getPlayerPos() {
    return this->player_pos;
}

std::vector<Positionable>& UI_Info::getStaticObjects() {
    return this->objects;
}

std::vector<DirectedPositionable>& UI_Info::getDirectedObjects() {
    return this->directed_objects;
}

PlayerView& UI_Info::getCameraPlanes() {
    return this->view;
}

std::vector<std::pair<int, int>>& UI_Info::getSliders() {
    return this->sliders;
}

std::vector<std::pair<int, float>> &UI_Info::getSounds() {
    return this->sounds;
}

bool UI_Info::isImportant() const {
    return important;
}


