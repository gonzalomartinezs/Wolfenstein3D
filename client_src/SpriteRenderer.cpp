#include "SpriteRenderer.h"
#include <cmath>
#include <algorithm>

#define TEX_HEIGHT 64
#define TEX_WIDTH 64
#define PI 3.141592


SpriteRenderer::SpriteRenderer(TexturesContainer &textures, int begin_x,
                               int begin_y, int width, int height):
        textures(textures), selector(textures),
        width(width), height(height), begin_x(begin_x),
        begin_y(begin_y), initialized(false){}

void SpriteRenderer::drawSprites(DirectedPositionable &player_pos, PlayerView view,
                            std::vector<DirectedPositionable> &directed_objects,
                            std::vector<Positionable> &objects,
                            const std::vector<float> &wall_dist) {
    if (!initialized) {
        selector.initializePlayers(directed_objects);
        initialized = (!directed_objects.empty());
    }
    selector.updatePlayers(directed_objects);
    std::vector<Positionable> directed_sprites;
    std::vector<Positionable> final_sprites;
    _selectDirectedSprite(player_pos, directed_objects, directed_sprites);
    _combineAndSortSprites(player_pos, objects, directed_sprites,
                           final_sprites);
    _renderizeSprites(player_pos, final_sprites, view.getPlaneX(),
                      view.getPlaneY(), wall_dist);
}

// ------------------------- Metodos privados --------------------------------//

// Selecciona el sprite correspondiente para cada direccionable y lo agrega al
// vector directed_sprites
void SpriteRenderer::_selectDirectedSprite(DirectedPositionable player_pos,
                                           std::vector<DirectedPositionable> &directed_objects,
                                           std::vector<Positionable> &directed_sprites) {
    for (DirectedPositionable positionable: directed_objects){
        TextureID texture = selector.selectTextureID(player_pos, positionable);
        Positionable directed_sprite(positionable.getX(), positionable.getY(),
                                     texture);
        directed_sprites.push_back(directed_sprite);
    }
}

// Combina los vectores de sprites en final_sprites y los ordena
// descendentemente de acuerdo a la distancia al jugador.
void
SpriteRenderer::_combineAndSortSprites(const DirectedPositionable &player_pos,
                                       std::vector<Positionable> &static_sprites,
                                       std::vector<Positionable> &directed_sprites,
                                       std::vector<Positionable> &final_sprites) {

    for (const Positionable& directed_sprite: directed_sprites) {
        final_sprites.push_back(directed_sprite);
    }
    for (const Positionable& static_sprite: static_sprites) {
        final_sprites.push_back(static_sprite);
    }
    std::sort(final_sprites.begin(), final_sprites.end(),
              [player_pos](const Positionable& a, const Positionable& b){
                  float distance_a = player_pos.distanceTo((Positionable&)a);
                  float distance_b = player_pos.distanceTo((Positionable&)b);
                  return distance_a > distance_b;
              });
}

// Renderiza los sprites en pantalla.
void SpriteRenderer::_renderizeSprites(DirectedPositionable &player_pos,
                                       std::vector<Positionable> &sprites,
                                       float camera_plane_x,
                                       float camera_plane_y,
                                       const std::vector<float> &wall_distances) {
    for (Positionable sprite: sprites){
        double sprite_x = sprite.getX() - player_pos.getX();
        double sprite_y = sprite.getY() - player_pos.getY();

        double inv_det = 1.0 / (camera_plane_x * player_pos.getDirY() -
                                camera_plane_y * player_pos.getDirX());

        // Calculo las posiciones del sprite dentro de la camara
        double transform_x = inv_det * (player_pos.getDirY() * sprite_x -
                                        player_pos.getDirX() * sprite_y);
        double transform_y = inv_det * (-camera_plane_y * sprite_x +
                                        camera_plane_x * sprite_y);

        SpriteInfo sp_info;
        _initializeSpriteInfo(sp_info, transform_x, transform_y, wall_distances);
        _showSprite(sp_info, sprite);
    }
}

// Carga en info toda la información necesaria para
void SpriteRenderer::_initializeSpriteInfo(SpriteInfo &info,
                                           double transform_x,
                                           double transform_y,
                                           const std::vector<float> &wall_distances) {
    int pixels_per_ray = 1;
    info.sprite_screen_x = int((this->width / 2.0) *
                               (1 + transform_x / transform_y));

    info.sprite_height = abs(int(this->height / (transform_y)));
    info.sprite_width = abs(int(this->height / (transform_y)));

    // Comienzo y final de sprite en eje y de ventana
    info.draw_start_y = -info.sprite_height / 2 + this->height / 2;
    if (info.draw_start_y < 0) info.draw_start_y = 0;
    info.draw_end_y = info.sprite_height / 2 + this->height / 2;
    if (info.draw_end_y >= this->height) info.draw_end_y = this->height - 1;

    // Comienzo y final de sprite en eje x de ventana (sin recortes).
    int draw_start_x = -info.sprite_width / 2 + info.sprite_screen_x;
    if (draw_start_x < 0) draw_start_x = 0;
    int draw_end_x = info.sprite_width / 2 + info.sprite_screen_x;
    if (draw_end_x >= this->width) draw_end_x = this->width - 1;

    // Comienzo y final de sprite en eje x de ventana (con recortes).
    info.sprite_begin = -1, info.sprite_end = -1;
    for(int i = draw_start_x; i < draw_end_x; i++) {
        if (transform_y > 0 && i >= 0 && i <= this->width &&
            transform_y < wall_distances[i/pixels_per_ray]) {
            if (info.sprite_begin == -1) info.sprite_begin = i;
            info.sprite_end = i;
        }
    }
}

// Muestra el sprite por pantalla
void SpriteRenderer::_showSprite(const SpriteInfo &info,
                                 Positionable &sprite) {
    if (info.sprite_begin != -1 && info.sprite_end != -1) {
        int sprite_height = TEX_HEIGHT;
        int sprite_width = TEX_WIDTH;
        if (sprite.getTexture() >= KnifeItem && sprite.getTexture() <= RPGItem){
            sprite_height*=2; // fix hasta conseguir texturas de igual tamaño
            sprite_width*=2;
        }
        int tex_x = int(sprite_width * (info.sprite_begin -
                            (-info.sprite_width / 2 + info.sprite_screen_x))
                            /info.sprite_width);
        int tex_width = ((info.sprite_end-info.sprite_begin)*sprite_width)
                                                            /info.sprite_width;

        SDL_Rect tex_portion;
        // Renderizo sprite en eje y entero
        if (info.sprite_height <= height){
            tex_portion =  {tex_x, 0, tex_width, sprite_height};
        } else {
            // Renderizo solo la porcion del eje y que entra en pantalla
            int portion = ((info.sprite_height-height)*sprite_height)/
                                                        (2*info.sprite_height);
            tex_portion =  {tex_x, portion, tex_width, sprite_height-2*portion};
        }

        SDL_Rect stretched = {info.sprite_begin + begin_x, info.draw_start_y + begin_y,
                              info.sprite_end-info.sprite_begin,
                              info.draw_end_y-info.draw_start_y};
        Texture* texture = selector.selectTexture(sprite);
        texture->render(&tex_portion, &stretched);
    }
}



