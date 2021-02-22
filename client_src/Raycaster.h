#ifndef RAYCASTER_H
#define RAYCASTER_H
#include <SDL2/SDL_render.h>
#include "SpriteRenderer.h"
#include "RaycastingRenderer.h"
#include "textures/TexturesContainer.h"
#include "../common_src/DirectedPositionable.h"
#include "../common_src/SlidingSurface.h"
#include "../common_src/Map.h"
#include "PlayerView.h"
#include "../common_src/Doors.h"

struct RayDirection{
    float x = 0;
    float y = 0;
};

class Raycaster {
private:
    Map& map;
    RaycastingRenderer renderer;
    SpriteRenderer sprite_renderer;
    std::vector<float> wall_distances;
    Doors doors;
    int width;
    int height;

public:
    // Pre: renderer se encuentra inicializado.
    // Post: crear un Raycaster listo para ser utilizado.
    Raycaster(Map &map, int begin_x, int begin_y, int width,
              int height, TexturesContainer &textures);

    // Pre: el VERSOR (dir_x, dir_y) y el vector (plane_x, plane_y)
    //      son perpendiculares.
    // Post: dibuja en el renderer la imagen raycasting generada.
    void draw(DirectedPositionable &player_pos, PlayerView &view,
              std::vector<Positionable> &objects,
              std::vector<DirectedPositionable> &directed_objects,
              std::vector<int> &doors_state, bool &not_playing);

    // Libera los recursos utilizados por el RayCaster
    ~Raycaster(){}



private:
    void _drawMap(const DirectedPositionable &player_pos, float camera_plane_x,
                  float camera_plane_y, bool not_playing);

    float _calculatePerpWallDist(DirectedPositionable &player, RayDirection ray_dir,
                                 char &hit_axis, int &map_x, int &map_y);

    static float _calculateSideDist(int &ray_dir_sign, float player_pos, float map_pos,
                             float delta_dist, float ray_dir);

    static void _calculateHitPoint(float &hit_x, float &hit_y, int map_x, int map_y,
                            char hit_axis, const DirectedPositionable& player,
                            RayDirection ray_dir);

    int _processSlidingPassage(float hit_x, float hit_y, int map_x, int map_y,
                               RayDirection ray_dir, float delta_dist_x,
                               float delta_dist_y, char hit_axis);

    static bool _rayHitsDoor(float ray_step_in, const ManualDoor &door);

};

#endif //RAYCASTER_H
