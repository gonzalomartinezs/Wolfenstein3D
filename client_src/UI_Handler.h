#ifndef UI_HANDLER_H
#define UI_HANDLER_H

#include <SDL2/SDL.h>
#include "Raycaster.h"
#include "textures/TexturesContainer.h"

class UI_Handler {
private:
    SDL_Renderer* renderer;
    Raycaster& raycaster;
    TexturesContainer& tex;
    SDL_Rect window;

public:
    // Crea un UI_Handler listo para ser utilizado.
    UI_Handler(SDL_Renderer *renderer, Raycaster &raycaster,
               TexturesContainer &tex, int width, int height);

    // Aplica el raycasting sobre el target de renderizado (no lo muestra por
    // pantalla)
    void raycast(DirectedPositionable player_pos, PlayerView view,
                 std::vector<Positionable> objects,
                 std::vector<DirectedPositionable> directed_objects);

    // Renderiza el contenido de la ventana.
    void render();

    // Limpia el contenido de la ventana.
    void clearScreen();

    // Carga la imagen de fondo del juego.
    void loadBackground();

    // Carga la interfaz informativa de los datos del jugador(vidas, salud, ...)
    void loadPlayerInterface();

    // Libera los recursos utilzador por el UI_Handler
    ~UI_Handler(){}
};


#endif //WOLFENSTEINCLIENT_UI_HANDLER_H
