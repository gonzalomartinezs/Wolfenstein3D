#include "TexturesContainer.h"
#define WALL_PATH "../client_src/textures/img/rocky.bmp"
#define BARREL_PATH "../client_src/textures/img/barrel.bmp"

TexturesContainer::TexturesContainer(SDL_Renderer* renderer): renderer(renderer){
    textures.emplace(None, nullptr);
    textures.emplace(Wall, new Texture(WALL_PATH, this->renderer));
    textures.emplace(Barrel, new Texture(BARREL_PATH, this->renderer));
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
