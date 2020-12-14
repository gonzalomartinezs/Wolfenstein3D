#include "Window.h"

Window::Window(std::string name, int width, int height, int pos_x, int pos_y,
               Uint32 flag) : width(width), height(height) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw ; // exception
    }
    this->window = SDL_CreateWindow(name.c_str(), pos_x, pos_y, width,
                                    height, flag);
    if (this->window == nullptr) {
        throw ; // exception
    }
    this->renderer = SDL_CreateRenderer(this->window, -1,
                                        SDL_RENDERER_ACCELERATED);
    if (this->renderer == nullptr) {
        throw ; // exception
    }
}

void Window::render() {
    SDL_RenderPresent(this->renderer);
}


void Window::clearScreen() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
}

SDL_Renderer *Window::getRenderer() const {
    return this->renderer;
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
}
