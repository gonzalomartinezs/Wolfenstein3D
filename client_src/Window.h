#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL.h>
#include <string>

class Window {
private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    // Crea una ventana del ancho y alto especificados.
    Window(std::string name, int width, int height, int pos_x, int pos_y,
           Uint32 flag);

    // Renderiza el contenido de la ventana.
    void render();

    // Retorna el renderer de la ventana.
    SDL_Renderer* getRenderer() const;

    // Libera los recursos utilizados por la ventana.
    ~Window();

};


#endif //WINDOW_H
