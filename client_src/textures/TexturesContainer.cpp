#include "TexturesContainer.h"
#define WALL_PATH "../client_src/textures/img/rocky.bmp"
#define BARREL_PATH "../client_src/textures/img/barrel.bmp"
#define GUARD_0_PATH "../client_src/textures/img/guard_0.bmp"
#define GUARD_1_PATH "../client_src/textures/img/guard_1.bmp"
#define GUARD_2_PATH "../client_src/textures/img/guard_2.bmp"
#define GUARD_3_PATH "../client_src/textures/img/guard_3.bmp"
#define GUARD_4_PATH "../client_src/textures/img/guard_4.bmp"
#define GUARD_5_PATH "../client_src/textures/img/guard_5.bmp"
#define GUARD_6_PATH "../client_src/textures/img/guard_6.bmp"
#define GUARD_7_PATH "../client_src/textures/img/guard_7.bmp"

TexturesContainer::TexturesContainer(SDL_Renderer* renderer): renderer(renderer){
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
}

Texture* TexturesContainer::get(TextureID id) {
    return textures[id];
}

TexturesContainer::~TexturesContainer() {
    for (std::pair<TextureID, Texture*> tex:textures){
        delete tex.second;
        tex.second = nullptr;
    }
}
