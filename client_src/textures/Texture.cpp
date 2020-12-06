#include "Texture.h"

Texture::Texture(std::string path, SDL_Renderer* renderer): renderer(renderer){
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL){
        throw ; //exception
    } else {
        texture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
        if( texture == NULL ){
            throw ; //exception
        }
        SDL_FreeSurface(loadedSurface);
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
