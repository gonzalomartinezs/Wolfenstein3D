#include "Texture.h"

#define R 152
#define G 0
#define B 136

Texture::Texture(std::string path, SDL_Renderer* renderer): renderer(renderer){
    SDL_Surface* loaded_surface = SDL_LoadBMP(path.c_str());
    if (loaded_surface == NULL){
        throw ; //exception
    } else {
        loaded_surface->format->Amask = 0xFF000000;
        loaded_surface->format->Ashift = 24;
        SDL_SetColorKey(loaded_surface, SDL_TRUE,
                        SDL_MapRGB(loaded_surface->format, R, G, B));
        texture = SDL_CreateTextureFromSurface(this->renderer, loaded_surface);
        if( texture == NULL ){
            throw ; //exception
        }
        SDL_FreeSurface(loaded_surface);
    }
}

void Texture::render(SDL_Rect *source, SDL_Rect *dest) {
    SDL_RenderCopy(this->renderer, this->texture, source, dest);
    SDL_RenderFillRect(this->renderer, source);

}

void Texture::changeColorModulation(Uint8 mod) {
    SDL_SetTextureColorMod(this->texture, mod, mod, mod);
}

Texture::~Texture() {
    if(this->texture){
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}
