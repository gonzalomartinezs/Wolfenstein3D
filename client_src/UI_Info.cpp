#include "UI_Info.h"

#include <utility>

UI_Info::UI_Info(DirectedPositionable player_pos, PlayerView view,
                 std::vector<int> player_info,
                 std::vector<Positionable> objects,
                 std::vector<DirectedPositionable> directed_objects,
                 std::vector<std::pair<int, int>> sliders_changes,
                 bool important) :
            player_pos(player_pos), player_info(std::move(player_info)),
            objects(std::move(objects)), sliders_changes(sliders_changes),
            directed_objects(std::move(directed_objects)), view(view),
            important(important){}


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

std::vector<std::pair<int, int>>& UI_Info::getSlidersChanges() {
    return this->sliders_changes;
}

bool UI_Info::isImportant() {
    return important;
}

