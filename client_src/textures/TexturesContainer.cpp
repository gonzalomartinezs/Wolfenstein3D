#include "TexturesContainer.h"
#include <SDL2/SDL_image.h>

#define WALL_PATH "../client_src/textures/img/sprites/rocky.bmp"
#define BARREL_PATH "../client_src/textures/img/sprites/barrel.bmp"
#define GUARD_0_PATH "../client_src/textures/img/sprites/guard_0.bmp"
#define GUARD_1_PATH "../client_src/textures/img/sprites/guard_1.bmp"
#define GUARD_2_PATH "../client_src/textures/img/sprites/guard_2.bmp"
#define GUARD_3_PATH "../client_src/textures/img/sprites/guard_3.bmp"
#define GUARD_4_PATH "../client_src/textures/img/sprites/guard_4.bmp"
#define GUARD_5_PATH "../client_src/textures/img/sprites/guard_5.bmp"
#define GUARD_6_PATH "../client_src/textures/img/sprites/guard_6.bmp"
#define GUARD_7_PATH "../client_src/textures/img/sprites/guard_7.bmp"
#define BACKGROUND "../client_src/textures/img/miscellaneous/back.png"
#define PL_INTERFACE "../client_src/textures/img/miscellaneous/interface_1.png"

TexturesContainer::TexturesContainer(SDL_Renderer *renderer,
                                     SDL_Surface *window_surface)
        : renderer(renderer), window_surface(window_surface){
    IMG_Init(IMG_INIT_PNG);
    textures.emplace(None, nullptr);
    textures.emplace(Wall, new Texture(WALL_PATH, this->renderer));
    textures.emplace(Barrel, new Texture(BARREL_PATH, this->renderer));
    textures.emplace(Guard_0, new Texture(GUARD_0_PATH, this->renderer));
    textures.emplace(Guard_1, new Texture(GUARD_1_PATH, this->renderer));
    textures.emplace(Guard_2, new Texture(GUARD_2_PATH, this->renderer));
    textures.emplace(Guard_3, new Texture(GUARD_3_PATH, this->renderer));
    textures.emplace(Guard_4, new Texture(GUARD_4_PATH, this->renderer));
    textures.emplace(Guard_5, new Texture(GUARD_5_PATH, this->renderer));
    textures.emplace(Guard_6, new Texture(GUARD_6_PATH, this->renderer));
    textures.emplace(Guard_7, new Texture(GUARD_7_PATH, this->renderer));
    textures.emplace(Background,new Texture(BACKGROUND,
                                        this->renderer, this->window_surface));
    textures.emplace(MainInterface, new Texture(PL_INTERFACE,
                                        this->renderer, this->window_surface));
}

Texture* TexturesContainer::get(TextureID id) {
    return textures[id];
}

TexturesContainer::~TexturesContainer() {
    for (std::pair<TextureID, Texture*> tex:textures){
        delete tex.second;
        tex.second = nullptr;
    }
    IMG_Quit();
}
