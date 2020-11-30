#ifndef RAYCASTER_H
#define RAYCASTER_H
#include <SDL2/SDL_render.h>
#include "Map.h"

class Raycaster {
private:
    Map& map;           // IMPORTANTE: la clase map debe tener un método get(x,y) que devuelve el entero en esa posicion
    SDL_Renderer& renderer;
    int width;
    int height;

public:
    // Pre: renderer se encuentra inicializado.
    // Post: crear un Raycaster listo para ser utilizado.
    Raycaster(Map& map, int width, int height, SDL_Renderer& renderer):
                map(map), renderer(renderer), width(width), height(height){}

    // Pre: el VERSOR (dir_x, dir_y) y el vector (plane_x, plane_y)
    //      son perpendiculares.
    // Post: dibuja en el renderer la imagen raycasting generada.
    void draw(float pos_x, float pos_y, float dir_x, float dir_y,
                                                float plane_x, float plane_y);

    // Libera los recursos utilizados por el RayCaster
    ~Raycaster(){}



private:
    void _renderize(float wall_dist, char hit_axis, int ray_number);
    float _calculatePerpWallDist(float player_pos_x, float player_pos_y,
                                 float ray_dir_x, float ray_dir_y,
                                 char *hit_axis);
    void _calculateSideDist(float *side_dist, int *ray_dir_sign,
                            float player_pos, float map_pos,
                            float delta_dist, float ray_dir);

};


#endif //RAYCASTER_H
