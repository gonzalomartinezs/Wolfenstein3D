#include "Window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

Window::Window(std::string name, int width, int height, int pos_x, int pos_y,
               Uint32 flag) : width(width), height(height) {
    int err_code_sdl = SDL_Init(SDL_INIT_VIDEO);
    if (err_code_sdl) throw ; // exception

    err_code_sdl = TTF_Init();
    if (err_code_sdl) throw ; // exception

    IMG_Init(IMG_INIT_PNG);

    this->window = SDL_CreateWindow(name.c_str(), pos_x, pos_y, width,
                                    height, flag);
    if (this->window == nullptr) throw ; // exception

    this->renderer = SDL_CreateRenderer(this->window, -1,
                                        SDL_RENDERER_ACCELERATED);
    if (this->renderer == nullptr) throw ; // exception
}

SDL_Renderer *Window::getRenderer() const {
    return this->renderer;
}

SDL_Surface *Window::getSurface() const {
    return SDL_GetWindowSurface(this->window);
}

Window::~Window() {
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }
    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
    if (TTF_WasInit()) TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


