#include <iostream>
#include "Raycaster.h"
#include "textures/TextureID.h"
#include "PlayerView.h"

#define VISUAL_PROPORTION 1.5
#define TEX_HEIGHT 64
#define TEX_WIDTH 64
#define ORIGINAL 255
#define SHADE 128

Raycaster::Raycaster(Map &map, int begin_x, int begin_y, int width, int height,
                     TexturesContainer &textures)
                     : map(map), begin_x(begin_x), begin_y(begin_y), width(width),
                     height(height), textures(textures),
                     sprite_renderer(textures, 0,0, width,height) {

    for(class Door door : map.getDoors()){
        std::string id = std::to_string(door.getX()) + "," + std::to_string(door.getY());
        this->doors.emplace(id, door);
    }
}

void Raycaster::draw(DirectedPositionable player_pos, PlayerView view,
                     std::vector<Positionable> objects,
                     std::vector<DirectedPositionable> directed_objects,
                     std::vector<std::tuple<int,int,int>> doors_changes) {

    for (auto& door_change:doors_changes){
        doors.at(std::to_string(std::get<0>(door_change)) + "," +
                std::to_string(std::get<1>(door_change)))
                .update(std::get<2>(door_change));
    }
    _drawMap(player_pos, view.getPlaneX(), view.getPlaneY());
    this->sprite_renderer.drawSprites(player_pos, view,directed_objects,
                                      objects, this->wall_distances);
    this->wall_distances.clear();
}



// ------------------------- Metodos privados --------------------------------//

// Dibuja las paredes del juego.
void Raycaster::_drawMap(DirectedPositionable player_pos, float camera_plane_x,
                         float camera_plane_y) {

    DirectedPositionable player = player_pos;
    RayDirection ray_dir;
    for(int i = 0; i < this->width; i++) {

        float alfa = (2*i) / (float)width - 1;
        ray_dir.x = player.getDirX() + camera_plane_x * alfa;
        ray_dir.y = player.getDirY() + camera_plane_y * alfa;
        int map_x = int(player.getX());
        int map_y = int(player.getY());
        char hit_axis;

        float perp_wall_dist = _calculatePerpWallDist(player, ray_dir,
                                                      hit_axis, map_x, map_y);
        this->wall_distances.push_back(perp_wall_dist);
        _renderize(perp_wall_dist, hit_axis, i, player, ray_dir, map_x, map_y);
    }
}


// Calcula la distancia euclidea entre el rayo perpendicular a la camara
// del jugador y la pared/objeto mas cercano.
float
Raycaster::_calculatePerpWallDist(DirectedPositionable &player, RayDirection ray_dir,
                                  char &hit_axis, int &map_x, int &map_y) {

    float delta_dist_x = std::sqrt(1+(ray_dir.y*ray_dir.y)/(ray_dir.x*ray_dir.x));
    float delta_dist_y = std::sqrt(1+(ray_dir.x*ray_dir.x)/(ray_dir.y*ray_dir.y));
    int ray_dir_x_sign, ray_dir_y_sign;

    float side_dist_x = _calculateSideDist(ray_dir_x_sign, player.getX(),
                                        float(map_x), delta_dist_x, ray_dir.x);
    float side_dist_y = _calculateSideDist(ray_dir_y_sign, player.getY(),
                                        float(map_y), delta_dist_y, ray_dir.y);

    bool hit = false;
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
        int current_cell = map.get(map_x, map_y);
        if(current_cell >= int(Door)){
            current_cell = _processDoor(map_x, map_y, player, ray_dir,
                                        delta_dist_x, delta_dist_y, hit_axis);
        }
        hit = (current_cell != 0);
    }

    float perp_wall_distance;
    if (hit_axis == 'x') {
        perp_wall_distance = (map_x - player.getX() + (1 - ray_dir_x_sign)/2) / ray_dir.x;
    } else {
        perp_wall_distance = (map_y - player.getY() + (1 - ray_dir_y_sign)/2) / ray_dir.y;
    }
    if (map.get(map_x, map_y) == 2) return perp_wall_distance*(1+0.5/perp_wall_distance);
    return perp_wall_distance;
}


// Calcula la distancia euclidea entre el rayo perpendicular a la camara
// del jugador y el limite de casilla mas cercano
float Raycaster::_calculateSideDist(int &ray_dir_sign, float player_pos,
                                    float map_pos,
                                    float delta_dist, float ray_dir) {
    float side_dist;
    if(ray_dir < 0) {
        ray_dir_sign = -1;
        side_dist = (player_pos - map_pos) * delta_dist;
    } else {
        ray_dir_sign = 1;
        side_dist = (map_pos + 1.0 - player_pos) * delta_dist;
    }
    return side_dist;
}


// Procesa la interseccion de un rayo con una puerta y retorna el numero de
// celda segun corresponda.
int Raycaster::_processDoor(int map_x, int map_y, DirectedPositionable player,
                            RayDirection ray_dir, float delta_dist_x,
                            float delta_dist_y, char hit_axis) {
    int corrected_map_x = map_x;
    int corrected_map_y = map_y;
    if (player.getX() < map_x) corrected_map_x--;
    if (player.getY() > map_y) corrected_map_y++;

    float ray_multiplicty;
    if (hit_axis == 'x'){
        ray_multiplicty = (corrected_map_x-player.getX()+1)/ray_dir.x;
    } else {
        ray_multiplicty = (corrected_map_y-player.getY())/ray_dir.y;
    }
    float hit_point_x = player.getX()+ray_dir.x*ray_multiplicty; // x de impacto
    float hit_point_y = player.getY()+ray_dir.y*ray_multiplicty; // y de impacto

    class Door door = doors.at(std::to_string(map_x) + "," + std::to_string(map_y));

    int ray_dir_x_sign = copysign(1, ray_dir.x);
    int ray_dir_y_sign = copysign(1, ray_dir.y);

    if (hit_axis == 'x'){
        float true_y_step = std::sqrt(delta_dist_x*delta_dist_x-1);
        float half_step_in_y = hit_point_y+(ray_dir_y_sign*true_y_step)/2;
        if (int(half_step_in_y)==map_y){
            float step_in = half_step_in_y-map_y;
            if (_rayHitsDoor(step_in, door)) return int(Door);
        }
    } else {
        float true_x_step = std::sqrt(delta_dist_y*delta_dist_y-1);
        float half_step_in_x = hit_point_x+(ray_dir_x_sign*true_x_step)/2;
        if (int(half_step_in_x)==map_x){
            float step_in = half_step_in_x-map_x;
            if (_rayHitsDoor(step_in, door)) return int(Door);
        }
    }
    return 0;
}

// Retorna un booleano que indica si el rayo colisiona con la puerta o no
bool Raycaster::_rayHitsDoor(float ray_step_in, class Door &door) {
    return ((door.isClosed()) ||
            (door.isClosing() && ray_step_in < door.getFractionRemaining()) ||
            (door.isOpening() && ray_step_in < 1-door.getFractionRemaining()));
}

// Renderiza el rayo actual en 'renderer'.
void Raycaster::_renderize(float wall_dist, char hit_axis, int ray_number,
                           DirectedPositionable player, RayDirection ray_dir,
                           int map_x, int map_y) {
    bool flip = false;
    int line_height = (int)(height/(wall_dist * VISUAL_PROPORTION));

    int draw_start = (-line_height/2) + (height/2);
    int draw_end = (line_height/2) + (height/2);
    if (draw_start < 0) draw_start = 0;
    if (draw_end >= height) draw_end = height - 1;

    int tex_id = map.get(map_x, map_y);

    int tex_x = _calculateTextureXCoordinate(player, ray_dir, wall_dist,
                                             hit_axis, ray_number);
    if(tex_id == int(Door))
        _processDoorTexture(tex_x, tex_id, map_x, map_y, ray_dir, hit_axis);

    Texture* texture = textures.get(TextureID(tex_id));
    SDL_Rect tex_portion;

    if (line_height <= height){
        tex_portion =  {tex_x, 0, 1, TEX_HEIGHT};
    } else {
        int portion = ((line_height-height)*TEX_HEIGHT)/(2*line_height);
        tex_portion =  {tex_x, portion, 1, TEX_HEIGHT-2*portion};
    }

    SDL_Rect stretched = {ray_number + begin_x, draw_start + begin_y,
                          1,draw_end-draw_start};
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

    int tex_x = int((wall_x+ray_number/width) * TEX_WIDTH);
    if (hit_axis == 'x' && ray_dir.x > 0)
        tex_x = TEX_WIDTH - tex_x - 1;
    if (hit_axis == 'y' && ray_dir.y < 0)
        tex_x = TEX_WIDTH - tex_x - 1;

    return tex_x;
}

// Reposiciona el inicio de la textura de la puerta de acuerdo al estado de la misma.
void
Raycaster::_processDoorTexture(int &tex_x, int &tex_id, int map_x, int map_y,
                               RayDirection ray_dir, char hit_axis) {
    class Door door = doors.at(std::to_string(map_x) + "," + std::to_string(map_y));
    if ((hit_axis == 'x' && ray_dir.x>0) || (hit_axis == 'y' && ray_dir.y<0)){
        if (door.isOpening()){
            tex_x -= door.getFractionRemaining()*TEX_WIDTH;
        } else if(door.isClosing()){
            tex_x -= (1 - door.getFractionRemaining())*TEX_WIDTH;
        }
    } else {
        if (door.isOpening()){
            tex_x += door.getFractionRemaining()*TEX_WIDTH;
        } else if(door.isClosing()){
            tex_x += (1 - door.getFractionRemaining())*TEX_WIDTH;
        }
        tex_id = int(InvertedDoor);
    }

}






