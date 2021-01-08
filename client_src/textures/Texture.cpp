#include "Texture.h"
#include <SDL2/SDL_image.h>
#include <iostream>

#define R 152
#define G 0
#define B 136

Texture::Texture(std::string path, SDL_Renderer* renderer,SDL_Surface* surface):
                                                            renderer(renderer){
    SDL_Surface* loaded_surface;
    if (path.substr(path.length()-3) == "bmp"){
        loaded_surface = SDL_LoadBMP(path.c_str());
        if(loaded_surface){
            loaded_surface->format->Amask = 0xFF000000;
            loaded_surface->format->Ashift = 24;
        }
    } else if (path.substr(path.length()-3) == "png" && surface){
        SDL_Surface* aux_surface = IMG_Load(path.c_str());
        if (aux_surface == nullptr) throw ; // exception
        loaded_surface = SDL_ConvertSurface(aux_surface, surface->format, 0);
        SDL_FreeSurface(aux_surface);
    } else throw ; // exception mandaste cualquier parametro bro

    if (loaded_surface == nullptr){
        throw ; //exception
    } else {
        SDL_SetColorKey(loaded_surface, SDL_TRUE,
                        SDL_MapRGB(loaded_surface->format, R, G, B));
        texture = SDL_CreateTextureFromSurface(this->renderer, loaded_surface);
        SDL_FreeSurface(loaded_surface);
        if (texture == nullptr){
            throw ; //exception
        }
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
