#include "FontTexture.h"
#include "../Exceptions/SDLException.h"

FontTexture::FontTexture(FontTexture&& other) noexcept{
    this->texture = other.texture;
    other.texture = nullptr;
    this->renderer = other.renderer;
    other.renderer = nullptr;
    this->font = other.font;
    other.font = nullptr;
    this->color = other.color;
    this->latest_value = other.latest_value;
}

FontTexture::FontTexture(std::string font_path, int font_size, SDL_Color font_color,
                         SDL_Renderer *renderer, std::string value) :
                         latest_value(value), renderer(renderer), color(font_color){
    this->font = TTF_OpenFont(font_path.c_str(), font_size);
    if (this->font == nullptr){
        throw SDLException("Unable to load font from path.");
    }

    SDL_Surface* loaded_surface = TTF_RenderText_Solid(this->font, value.c_str(), font_color);
    if (loaded_surface == nullptr){
        throw SDLException("Failed to create surface.");
    } else {
        this->texture = SDL_CreateTextureFromSurface(this->renderer, loaded_surface);
        SDL_FreeSurface(loaded_surface);
        if (this->texture == nullptr){
            throw SDLException("Unable to create font texture.");
        }
    }
}

void FontTexture::renderHorizontallyCentered(std::string new_value,
                                             SDL_Rect *source, SDL_Rect *dest) {
    // cambio textura si el valor fue modificado
    if (new_value != this->latest_value){
        this->latest_value = new_value;
        SDL_Surface* loaded_surface = TTF_RenderText_Solid(this->font,
                                                           latest_value.c_str(),
                                                           this->color);
        if (loaded_surface == nullptr){
            throw SDLException("Failed to create surface.");
        } else {
            SDL_DestroyTexture(this->texture);
            this->texture = SDL_CreateTextureFromSurface(this->renderer, loaded_surface);
            SDL_FreeSurface(loaded_surface);
            if (this->texture == nullptr){
                throw SDLException("Unable to create font texture.");
            }
        }
    }
    int tex_width, tex_height;
    SDL_QueryTexture(this->texture, nullptr, nullptr, &tex_width, &tex_height);
    int x_pos = dest->x + (dest->w - tex_width)/2;
    SDL_Rect centered_dest = {x_pos, dest->y, tex_width, tex_height};
    SDL_RenderCopy(this->renderer, this->texture, source, &centered_dest);
}

FontTexture::~FontTexture() {
    if(this->font){
        TTF_CloseFont(this->font);
        this->font = nullptr;
    }
    if(this->texture){
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}

