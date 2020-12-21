#ifndef RAYCASTER_H
#define RAYCASTER_H
#include <SDL2/SDL_render.h>
#include "SpriteRenderer.h"
#include "textures/TexturesContainer.h"
#include "../common_src/DirectedPositionable.h"
#include "../common_src/Map.h"
#include "PlayerView.h"

struct RayDirection{
    float x = 0;
    float y = 0;
};

class Raycaster {
private:
    Map& map;
    TexturesContainer& textures;
    SpriteRenderer sprite_renderer;
    std::vector<float> wall_distances;
    int width;
    int height;

public:
    // Pre: renderer se encuentra inicializado.
    // Post: crear un Raycaster listo para ser utilizado.
    Raycaster(Map &map, int width, int height, TexturesContainer &textures);

    // Pre: el VERSOR (dir_x, dir_y) y el vector (plane_x, plane_y)
    //      son perpendiculares.
    // Post: dibuja en el renderer la imagen raycasting generada.
    void draw(DirectedPositionable player_pos, PlayerView view,
              std::vector<Positionable> objects,
              std::vector<DirectedPositionable> directed_objects);

    // Libera los recursos utilizados por el RayCaster
    ~Raycaster(){}



private:
    void _drawMap(DirectedPositionable player_pos, float camera_plane_x,
                  float camera_plane_y);

    void _renderize(float wall_dist, char hit_axis, int ray_number,
                    DirectedPositionable player, RayDirection ray_dir,
                    int map_x, int map_y);

    float _calculatePerpWallDist(DirectedPositionable &player, RayDirection ray_dir,
                                 char &hit_axis, int &map_x, int &map_y);

    void _calculateSideDist(float &side_dist, int &ray_dir_sign,
                            float player_pos, float map_pos,
                            float delta_dist, float ray_dir);

    int _calculateTextureXCoordinate(DirectedPositionable player,
                                     RayDirection ray_dir,
                                     float wall_dist, char hit_axis,
                                     int ray_number);

};

#endif //RAYCASTER_H
