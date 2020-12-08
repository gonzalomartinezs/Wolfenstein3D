#ifndef RAYCASTER_H
#define RAYCASTER_H
#include <SDL2/SDL_render.h>
#include "textures/TexturesContainer.h"
#include "../common_src/PlayerPosition.h"
#include "../common_src/Map.h"

struct RayDirection{
    float x = 0;
    float y = 0;
};

class Raycaster {
private:
    Map& map;           // IMPORTANTE: la clase map debe tener un método get(x,y) que devuelve el entero en esa posicion
    SDL_Renderer& renderer;
    TexturesContainer& textures;
    int width;
    int height;


public:
    // Pre: renderer se encuentra inicializado.
    // Post: crear un Raycaster listo para ser utilizado.
    Raycaster(Map &map, int width, int height, SDL_Renderer &renderer,
              TexturesContainer &textures):map(map), renderer(renderer),
                                           textures(textures), width(width), height(height){}

    // Pre: el VERSOR (dir_x, dir_y) y el vector (plane_x, plane_y)
    //      son perpendiculares.
    // Post: dibuja en el renderer la imagen raycasting generada.
    void draw(PlayerPosition player_pos, float camera_plane_x,
              float camera_plane_y);

    // Libera los recursos utilizados por el RayCaster
    ~Raycaster(){}


private:
    void _renderize(float wall_dist, char hit_axis, int ray_number,
                    PlayerPosition player, RayDirection ray_dir,
                    int map_x, int map_y);

    float _calculatePerpWallDist(PlayerPosition &player, RayDirection ray_dir,
                                 char &hit_axis, int &map_x, int &map_y);

    void _calculateSideDist(float &side_dist, int &ray_dir_sign,
                            float player_pos, float map_pos,
                            float delta_dist, float ray_dir);

    int _calculateTextureXCoordinate(PlayerPosition player,
                                     RayDirection ray_dir,
                                     float wall_dist, char hit_axis,
                                     int ray_number);

};

#endif //RAYCASTER_H
