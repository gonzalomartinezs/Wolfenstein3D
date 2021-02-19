#include <iostream>
#include "Raycaster.h"
#include "textures/TextureID.h"
#include "PlayerView.h"
#include "../common_src/GameConstants.h"

Raycaster::Raycaster(Map &map, int begin_x, int begin_y, int width, int height,
                     TexturesContainer &textures)
                     : map(map), width(width), height(height),
                     renderer(textures, map, nullptr, begin_x, begin_y, width, height),
                     sprite_renderer(textures, begin_x, begin_y, width, height) {

    for(auto& surface : map.getSlidingSurfaces()){
        this->surfaces.emplace(surface.getId(), surface);
    }
    this->renderer.updateSurfaces(&surfaces);
}

void Raycaster::draw(DirectedPositionable player_pos, PlayerView view,
                     std::vector<Positionable> objects,
                     std::vector<DirectedPositionable> directed_objects,
                     std::vector<std::pair<int,int>> sliders_changes) {

    for (auto& slider: sliders_changes) // cambio estado de superficies modificadas
        surfaces.at(slider.first).update(slider.second);

    for (auto& surface: surfaces) // actualizo todas las superficies
        surface.second.update(surface.second.getState());

    _drawMap(player_pos, view.getPlaneX(), view.getPlaneY());
    this->sprite_renderer.drawSprites(player_pos, view,directed_objects,
                                      objects, this->wall_distances);
    this->wall_distances.clear();
}



// ------------------------- Metodos privados --------------------------------//

// Dibuja las paredes del juego.
void Raycaster::_drawMap(const DirectedPositionable& player_pos, float camera_plane_x,
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
        this->renderer.render(perp_wall_dist, hit_axis, i, player, ray_dir, map_x, map_y);
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
        if (current_cell >= DOOR_CLOSED) {
            float hit_x, hit_y;
            _calculateHitPoint(hit_x, hit_y, map_x, map_y, hit_axis, player, ray_dir);
            current_cell = _processSlidingPassage(hit_x, hit_y, map_x, map_y,ray_dir,
                                                  delta_dist_x, delta_dist_y,hit_axis);
        }
        hit = (current_cell != 0);
    }
    float perp_wall_distance;
    if (hit_axis == 'x') {
        perp_wall_distance = (map_x - player.getX() + (1 - ray_dir_x_sign)/2) / ray_dir.x;
    } else {
        perp_wall_distance = (map_y - player.getY() + (1 - ray_dir_y_sign)/2) / ray_dir.y;
    }
    if (map.get(map_x, map_y) == DOOR)
        return perp_wall_distance * (1 + 0.5 / perp_wall_distance);
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

// Calculas las coordenadas x e y de impacto del rayo en la celda
void Raycaster::_calculateHitPoint(float &hit_x, float &hit_y, int map_x, int map_y,
                              char hit_axis, const DirectedPositionable& player,
                              RayDirection ray_dir) {
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
    hit_x = player.getX()+ray_dir.x*ray_multiplicty; // x de impacto
    hit_y = player.getY()+ray_dir.y*ray_multiplicty; // y de impacto
}


// Procesa la interseccion de un rayo con una superficie deslizante
// y retorna el numero de celda segun corresponda.
int Raycaster::_processSlidingPassage(float hit_x, float hit_y, int map_x, int map_y,
                                      RayDirection ray_dir, float delta_dist_x,
                                      float delta_dist_y, char hit_axis) {
    int id;
    for(auto& surface: surfaces){
        if(surface.second.getX() == map_x && surface.second.getY() == map_y)
            id = surface.first;
    }
    int ray_dir_x_sign = copysign(1, ray_dir.x);
    int ray_dir_y_sign = copysign(1, ray_dir.y);

    float fraction = 0;
    if (surfaces.at(id).getSurfaceType() == DOOR) fraction = 0.5;

    if (hit_axis == 'x'){
        float true_y_step = std::sqrt(delta_dist_x*delta_dist_x-1);
        float half_step_in_y = hit_y+(ray_dir_y_sign*true_y_step)*fraction;
        if (int(half_step_in_y)==map_y){
            float step_in = half_step_in_y-map_y;
            if (_rayHitsSurface(step_in, surfaces.at(id))) return int(Door);
        }
    } else {
        float true_x_step = std::sqrt(delta_dist_y*delta_dist_y-1);
        float half_step_in_x = hit_x+(ray_dir_x_sign*true_x_step)*fraction;
        if (int(half_step_in_x)==map_x){
            float step_in = half_step_in_x-map_x;
            if (_rayHitsSurface(step_in, surfaces.at(id))) return int(Door);
        }
    }
    return 0;
}

// Retorna un booleano que indica si el rayo colisiona con la
// superficie deslizante o no.
bool Raycaster::_rayHitsSurface(float ray_step_in, const SlidingSurface& surface) {
    return ((surface.isClosed()) ||
            (surface.isClosing() && ray_step_in < surface.getElapsedFraction()) ||
            (surface.isOpening() && ray_step_in < 1 - surface.getElapsedFraction()));
}


