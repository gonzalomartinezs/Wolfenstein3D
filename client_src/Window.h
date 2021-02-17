#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL.h>
#include <string>

class Window {
private:
    int width;
    int height;
    bool sdl_initiated;
    bool img_initiated;
    bool mixer_initiated;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    // Crea una ventana del ancho y alto especificados.
    Window(std::string name, int width, int height, int pos_x, int pos_y,
           Uint32 flag);

    // Retorna el renderer de la ventana.
    SDL_Renderer* getRenderer() const;

    // Retorna la superficie de la ventana.
    SDL_Surface* getSurface() const;

    // Libera los recursos utilizados por la ventana.
    ~Window();

};


#endif //WINDOW_H
