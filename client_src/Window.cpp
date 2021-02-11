#include "Window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../common_src/Exceptions/WindowException.h"

Window::Window(std::string name, int width, int height, int pos_x, int pos_y,
               Uint32 flag) : width(width), height(height), sdl_initiated(false),
                              img_initiated(false) {
    int err_code_sdl = SDL_Init(SDL_INIT_VIDEO);
    if (err_code_sdl) throw WindowException("Failed to initiate SDL.");
    sdl_initiated = true;

    err_code_sdl = TTF_Init();
    if (err_code_sdl) throw WindowException("Failed to initiate SDL_ttf.");
    img_initiated = true;

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) throw WindowException("Failed to initiate SDL_image.");

    this->window = SDL_CreateWindow(name.c_str(), pos_x, pos_y, width,
                                    height, flag);
    if (this->window == nullptr) throw WindowException("Failed to create window.");

    this->renderer = SDL_CreateRenderer(this->window, -1,
                                        SDL_RENDERER_ACCELERATED);
    if (this->renderer == nullptr) throw WindowException("Failed to create renderer.");
}

SDL_Renderer *Window::getRenderer() const {
    return this->renderer;
}

SDL_Surface *Window::getSurface() const {
    return SDL_GetWindowSurface(this->window);
}

Window::~Window() {
    // Con un par de objetitos RAII se ahorraban estos bools (ver el double buffer de la clase de Martín)
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }
    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
    if (TTF_WasInit()) TTF_Quit();
    if (img_initiated) IMG_Quit();
    if (sdl_initiated) SDL_Quit();
}


