#ifndef RAYCASTINGRENDERER_H
#define RAYCASTINGRENDERER_H
#include "textures/TexturesContainer.h"
#include "../common_src/DirectedPositionable.h"
#include "../common_src/SlidingSurface.h"
#include "../common_src/Map.h"
#include "PlayerView.h"
#include "../common_src/Doors.h"

struct RayDirection;

class RaycastingRenderer {
private:
    Map& map;
    TexturesContainer& textures;
    Doors& doors;
    int width;
    int height;
    int begin_x;
    int begin_y;

public:
    RaycastingRenderer(TexturesContainer &textures, Map& map, Doors& doors,
                       int begin_x, int begin_y, int width, int height);

    void render(float wall_dist, char hit_axis, int ray_number,
                const DirectedPositionable& player, RayDirection ray_dir,
                int map_x, int map_y);

    ~RaycastingRenderer(){}

private:
    int _calculateTextureXCoordinate(const DirectedPositionable& player, RayDirection ray_dir,
                                     float wall_dist, char hit_axis, int ray_number) const;

    void _processSurfaceTexture(int &tex_x, int &tex_id, int map_x, int map_y,
                                RayDirection ray_dir, char hit_axis);
};


#endif //RAYCASTINGRENDERER_H
