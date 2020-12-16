#include "ProtectedDrawingInfo.h"

void ProtectedDrawingInfo::update(DirectedPositionable player_pos,
                                  std::vector<Positionable> &objects,
                                  std::vector<DirectedPositionable> &directed_objects,
                                  float camera_plane_x, float camera_plane_y) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->info.player_pos = player_pos;
    this->info.objects = objects;
    this->info.directed_objects = directed_objects;
    this->info.camera_plane_x = camera_plane_x;
    this->info.camera_plane_y = camera_plane_y;
}

DrawingInfo ProtectedDrawingInfo::getDrawingInfo() {
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->info;
}
