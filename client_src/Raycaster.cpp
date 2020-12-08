#include "Raycaster.h"
#include "textures/TextureID.h"
#define RAY_AMOUNT 320
#define VISUAL_PROPORTION 1.5
#define TEX_HEIGHT 64
#define TEX_WIDTH 64
#define ORIGINAL 255
#define SHADE 128


void Raycaster::draw(DirectedPositionable player_pos, float camera_plane_x,
                     float camera_plane_y) {

    DirectedPositionable player = player_pos;
    RayDirection ray_dir;
    for(int i = 0; i < RAY_AMOUNT; i++) {

        float alfa = (2*i) / (float)RAY_AMOUNT - 1;
        ray_dir.x = player.getDirX() + camera_plane_x * alfa;
        ray_dir.y = player.getDirY() + camera_plane_y * alfa;
        int map_x = int(player.getX());
        int map_y = int(player.getY());
        char hit_axis;

        float perp_wall_dist = _calculatePerpWallDist(player, ray_dir,
                                                      hit_axis, map_x, map_y);

        _renderize(perp_wall_dist, hit_axis, i, player, ray_dir, map_x, map_y);
    }
}

// ------------------------- Metodos privados --------------------------------//

// Calcula la distancia euclidea entre el rayo perpendicular a la camara
// del jugador y la pared/objeto mas cercano.
float
Raycaster::_calculatePerpWallDist(DirectedPositionable player, RayDirection ray_dir,
                                  char &hit_axis, int &map_x, int &map_y) {

    float side_dist_x, side_dist_y;
    float delta_dist_x = std::abs(1 / ray_dir.x);
    float delta_dist_y = std::abs(1 / ray_dir.y);

    int ray_dir_x_sign, ray_dir_y_sign;

    _calculateSideDist(side_dist_x, ray_dir_x_sign, player.getX(),
                       float(map_x), delta_dist_x, ray_dir.x);
    _calculateSideDist(side_dist_y, ray_dir_y_sign, player.getY(),
                       float(map_y), delta_dist_y, ray_dir.y);

    bool hit= false;
    while (!hit) {
        if(side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += ray_dir_x_sign;
            hit_axis = 'x';
        } else {
            side_dist_y += delta_dist_y;
            map_y += ray_dir_y_sign;
            hit_axis = 'y';
        }
        hit = (map.get(map_x, map_y) > 0);
    }

    if (hit_axis == 'x') {
        return (map_x - player.getX() + (1 - ray_dir_x_sign)/2) / ray_dir.x;
    }
    return (map_y - player.getY() + (1 - ray_dir_y_sign)/2) / ray_dir.y;
}


// Calcula la distancia euclidea entre el rayo perpendicular a la camara
// del jugador y el limite de casilla mas cercano
void Raycaster::_calculateSideDist(float &side_dist, int &ray_dir_sign,
                                   float player_pos, float map_pos,
                                   float delta_dist, float ray_dir) {
    if(ray_dir < 0) {
        ray_dir_sign = -1;
        side_dist = (player_pos - map_pos) * delta_dist;
    } else {
        ray_dir_sign = 1;
        side_dist = (map_pos + 1.0 - player_pos) * delta_dist;
    }
}


// Renderiza el rayo actual en 'renderer'.
void Raycaster::_renderize(float wall_dist, char hit_axis, int ray_number,
                           DirectedPositionable player, RayDirection ray_dir,
                           int map_x, int map_y) {

    int line_height = (int)(height/(wall_dist * VISUAL_PROPORTION));

    int draw_start = (-line_height/2) + (height/2);
    int draw_end = (line_height/2) + (height/2);
    if (draw_start < 0) draw_start = 0;
    if (draw_end >= height) draw_end = height - 1;

    int tex_id = map.get(map_x, map_y) - 1;
    Texture* texture = textures.get(TextureID(tex_id));

    int tex_x = _calculateTextureXCoordinate(player, ray_dir, wall_dist,
                                             hit_axis, ray_number);
    SDL_Rect tex_portion;

    if (line_height <= height){
        tex_portion =  {tex_x, 0, 1, TEX_HEIGHT};
    } else {
        int portion = ((line_height-height)*TEX_HEIGHT)/(2*line_height);
        tex_portion =  {tex_x, portion, 1, TEX_HEIGHT-2*portion};
    }

    int band_width =  width/RAY_AMOUNT;
    SDL_Rect stretched = {ray_number*band_width, draw_start, band_width,
                          draw_end-draw_start};
    if (hit_axis == 'y'){
        texture->changeColorModulation(SHADE);
    }
    texture->render(&tex_portion, &stretched);
    texture->changeColorModulation(ORIGINAL); // vuelvo al color original
}

// Calcula la coordenada x de la textura que se debe graficar.
int Raycaster::_calculateTextureXCoordinate(DirectedPositionable player,
                                            RayDirection ray_dir,
                                            float wall_dist, char hit_axis,
                                            int ray_number) {
    double wall_x;
    if (hit_axis == 'x')
        wall_x = player.getY() + wall_dist * ray_dir.y;
    else
        wall_x = player.getX() + wall_dist * ray_dir.x;
    wall_x -= int((wall_x));

    int tex_x = int((wall_x+ray_number/RAY_AMOUNT) * TEX_WIDTH);
    if (hit_axis == 'x' && ray_dir.x > 0)
        tex_x = TEX_WIDTH - tex_x - 1;
    if (hit_axis == 'y' && ray_dir.y < 0)
        tex_x = TEX_WIDTH - tex_x - 1;

    return tex_x;
}


