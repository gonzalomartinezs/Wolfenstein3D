#include "PlayerView.h"

void PlayerView::movePlaneX(float movement) {
    this->camera_plane_x = movement;
}

void PlayerView::movePlaneY(float movement) {
    this->camera_plane_y = movement;
}

float PlayerView::getPlaneX() const {
    return this->camera_plane_x;
}

float PlayerView::getPlaneY() const {
    return this->camera_plane_y;
}
