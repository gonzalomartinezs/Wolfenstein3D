#ifndef PROTECTEDDRAWINGINFO_H
#define PROTECTEDDRAWINGINFO_H

#include <mutex>
#include <vector>
#include "../common_src/DirectedPositionable.h"
#include "../common_src/Positionable.h"

struct DrawingInfo {
    DirectedPositionable player_pos = DirectedPositionable(0,0,0,0);
    std::vector<Positionable> objects;
    std::vector<DirectedPositionable> directed_objects;
    float camera_plane_x = 0.0;
    float camera_plane_y = 0.0;
};

class ProtectedDrawingInfo {
private:
    DrawingInfo info;
    std::mutex mutex;

public:
    // Crea un ProtectedDrawingInfo listo para ser utilizado.
    ProtectedDrawingInfo(){}

    // Actualiza la información del objeto.
    void update(DirectedPositionable player_pos, std::vector<Positionable> &objects,
                std::vector<DirectedPositionable> &directed_objects,
                float camera_plane_x, float camera_plane_y);

    // Retorna una copia de la información de renderizado.
    DrawingInfo getDrawingInfo();

    ~ProtectedDrawingInfo(){}
};


#endif //PROTECTEDDRAWINGINFO_H
