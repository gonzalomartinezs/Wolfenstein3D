#include "Raycaster.h"
#define VISUAL_PROPORTION 1.5

void Raycaster::draw(float player_pos_x, float player_pos_y,
                     float player_dir_x, float player_dir_y,
                     float camera_plane_x, float camera_plane_y) {

    for(int i = 0; i < width; i++) {

        float alfa = (2*i) / (float)width - 1;
        float ray_dir_x = player_dir_x + camera_plane_x * alfa;
        float ray_dir_y = player_dir_y + camera_plane_y * alfa;
        char hit_axis;

        float perp_wall_dist = _calculatePerpWallDist(player_pos_x,
                              player_pos_y, ray_dir_x, ray_dir_y, &hit_axis);

        _renderize(perp_wall_dist, hit_axis, i);
    }
}

// ------------------------- Metodos privados --------------------------------//

// Calcula la distancia euclidea entre el rayo perpendicular a la camara
// del jugador y la pared/objeto mas cercano.
float Raycaster::_calculatePerpWallDist(float player_pos_x, float player_pos_y,
                                        float ray_dir_x, float ray_dir_y,
                                        char *hit_axis) {
    int map_x = int(player_pos_x);
    int map_y = int(player_pos_y);

    float side_dist_x, side_dist_y;
    float delta_dist_x = std::abs(1 / ray_dir_x);
    float delta_dist_y = std::abs(1 / ray_dir_y);

    int ray_dir_x_sign, ray_dir_y_sign;

    _calculateSideDist(&side_dist_x, &ray_dir_x_sign, player_pos_x,
                                        float(map_x), delta_dist_x, ray_dir_x);
    _calculateSideDist(&side_dist_y, &ray_dir_y_sign, player_pos_y,
                                        float(map_y), delta_dist_y, ray_dir_y);

    bool hit= false;
    while (!hit) {
        if(side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += ray_dir_x_sign;
            *hit_axis = 'x';
        } else {
            side_dist_y += delta_dist_y;
            map_y += ray_dir_y_sign;
            *hit_axis = 'y';
        }
        hit = (map.get(map_x, map_y) > 0);
    }

    if (*hit_axis == 'x') {
        return (map_x - player_pos_x + (1 - ray_dir_x_sign) / 2) / ray_dir_x;
    }
    return (map_y - player_pos_y + (1 - ray_dir_y_sign) / 2) / ray_dir_y;
}


// Calcula la distancia euclidea entre el rayo perpendicular a la camara
// del jugador y el limite de casilla mas cercano
void Raycaster::_calculateSideDist(float *side_dist, int *ray_dir_sign,
                                   float player_pos, float map_pos,
                                   float delta_dist, float ray_dir) {
    if(ray_dir < 0) {
        *ray_dir_sign = -1;
        *side_dist = (player_pos - map_pos) * delta_dist;
    } else {
        *ray_dir_sign = 1;
        *side_dist = (map_pos + 1.0 - player_pos) * delta_dist;
    }
}


// Renderiza el rayo actual en 'renderer'.
void Raycaster::_renderize(float wall_dist, char hit_axis, int ray_number) {
    int lineHeight = (int)(height/(wall_dist * VISUAL_PROPORTION));

    int draw_start = (-lineHeight/2) + (height/2);
    int draw_end = (lineHeight/2) + (height/2);
    if (draw_start < 0) draw_start = 0;
    if (draw_end >= height) draw_end = height - 1;
    // esto dibuja las paredes
    if (hit_axis == 'x'){
        SDL_SetRenderDrawColor(&renderer, 0x6B, 0xB4, 0x6E, 0xFF);
    } else {
        SDL_SetRenderDrawColor(&renderer, 0x6B, 0x9A, 0x6E, 0xFF);
    }
    SDL_Rect rectangle = {ray_number, draw_start, 1, draw_end-draw_start};
    SDL_RenderFillRect(&renderer, &rectangle);
}

