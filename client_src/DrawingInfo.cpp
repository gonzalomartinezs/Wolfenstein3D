#include "DrawingInfo.h"

DrawingInfo::DrawingInfo(DirectedPositionable player_pos,
                         std::vector<Positionable> objects,
                         std::vector<DirectedPositionable> directed_objects,
                         float camera_plane_x, float camera_plane_y):
            player_pos(player_pos), objects(objects),
            directed_objects(directed_objects), camera_plane_x(camera_plane_x),
            camera_plane_y(camera_plane_y){}

DirectedPositionable DrawingInfo::getPlayerPos() {
    return this->player_pos;
}

std::vector<Positionable> DrawingInfo::getStaticObjects() {
    return this->objects;
}

std::vector<DirectedPositionable> DrawingInfo::getDirectedObjects() {
    return this->directed_objects;
}

float DrawingInfo::getCameraPlaneX() {
    return this->camera_plane_x;
}


float DrawingInfo::getCameraPlaneY() {
    return this->camera_plane_y;
}
