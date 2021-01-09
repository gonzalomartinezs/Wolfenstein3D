#ifndef TEXTURERENDERER_H
#define TEXTURERENDERER_H
#include <vector>
#include "textures/TexturesContainer.h"
#include "../common_src/DirectedPositionable.h"
#include "PlayerView.h"

#define RAY_AMOUNT 320

struct SpriteInfo {
    // Porporciones de sprite en pantalla.
    int sprite_height;
    int sprite_width;
    // Coordenada en x del centro de sprite en pantalla.
    int sprite_screen_x;
    // Cotas de renderizado de sprite en eje y de pantalla.
    int draw_start_y;
    int draw_end_y;
    // Comienzo y final de sprite en eje x de ventana (con recortes).
    int sprite_begin;
    int sprite_end;
};


class SpriteRenderer {
private:
    TexturesContainer& textures;
    int width;
    int height;
    int begin_x;
    int begin_y;

public:
    // Pre: renderer se encuentra inicializado.
    // Post: Crea un spriteRenderer listo para ser utilizado.
    SpriteRenderer(TexturesContainer &textures, int begin_x, int begin_y,
                   int width, int height) : textures(textures), width(width), height(height){}

    // Renderiza en la pantalla los sprites del juego
    void drawSprites(DirectedPositionable &player_pos, PlayerView view,
                     std::vector<DirectedPositionable> &directed_objects,
                     std::vector<Positionable> &objects,
                     const std::vector<float> &wall_dist);

    // Libera los recursos utilizados por el spriteRenderer
    ~SpriteRenderer(){}

private:
    static void _selectDirectedSprite(DirectedPositionable player_pos,
                               std::vector<DirectedPositionable> &directed_objects,
                               std::vector<Positionable> &directed_sprites);

    static void _combineAndSortSprites(const DirectedPositionable &player_pos,
                                       std::vector<Positionable> &static_sprites,
                                       std::vector<Positionable> &directed_sprites,
                                       std::vector<Positionable> &final_sprites);

    void _renderizeSprites(DirectedPositionable &player_pos,
                                  std::vector<Positionable> &sprites,
                                  float camera_plane_x, float camera_plane_y,
                                  const std::vector<float> &wall_distances);

    void _initializeSpriteInfo(SpriteInfo &info,
                                double transform_x,
                                double transform_y,
                                const std::vector<float> &wall_distances);

    void _showSprite(const SpriteInfo& info, Positionable &sprite);

    static float _distance(float x_1, float y_1, float x_2, float y_2);

    static float _calculateAngle(const DirectedPositionable& sprite,
                                 const Positionable& player_pos);
};


#endif //TEXTURERENDERER_H
