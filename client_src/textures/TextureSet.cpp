#include "TextureSet.h"
#include "../../common_src/Exceptions/WolfensteinException.h"

TextureSet::TextureSet(std::vector<std::string> paths, SDL_Renderer *renderer,
                       SDL_Surface *surface, unsigned period): period(period) {
    textures.reserve(paths.size());
    for (auto& path: paths){
        textures.emplace_back(path, renderer, surface);
    }
}

Texture &TextureSet::get(int i) {
    if (i > textures.size() || i < 0) {
        throw WolfensteinException("Index out of range");
    }
    return textures[i];
}

unsigned TextureSet::getPeriod() {
    return period;
}

size_t TextureSet::size() {
    return textures.size();
}

TextureSet::~TextureSet() {}

