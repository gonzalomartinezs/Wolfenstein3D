#ifndef PROTECTEDDRAWINGINFO_H
#define PROTECTEDDRAWINGINFO_H

#include <mutex>
#include <vector>
#include "../common_src/DirectedPositionable.h"
#include "../common_src/Positionable.h"


class DrawingInfo {
private:
    DirectedPositionable player_pos;
    std::vector<Positionable> objects;
    std::vector<DirectedPositionable> directed_objects;
    float camera_plane_x;
    float camera_plane_y;

public:
    // Crea un DrawingInfo listo para ser utilizado.
    DrawingInfo(DirectedPositionable player_pos, std::vector<Positionable> objects,
                std::vector<DirectedPositionable> directed_objects,
                float camera_plane_x, float camera_plane_y);

    DirectedPositionable getPlayerPos();
    std::vector<Positionable> getStaticObjects();
    std::vector<DirectedPositionable> getDirectedObjects();
    float getCameraPlaneX();
    float getCameraPlaneY();

    // Libera los recursos utilzados por el objecto.
    ~DrawingInfo(){}
};


#endif //PROTECTEDDRAWINGINFO_H
