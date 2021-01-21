#ifndef UI_HANDLER_H
#define UI_HANDLER_H

#include <SDL2/SDL.h>
#include "Raycaster.h"
#include "textures/TexturesContainer.h"
#include "textures/FontTexture.h"

struct InterfaceElements{
    SDL_Rect score;
    SDL_Rect lives;
    SDL_Rect hp;
    SDL_Rect key;
    SDL_Rect weapon;
    SDL_Rect ammo;
    SDL_Rect bj_face;
};

class UI_Handler {
private:
    SDL_Renderer* renderer;
    Raycaster& raycaster;
    TexturesContainer& tex;
    InterfaceElements elements;
    std::vector<FontTexture> font_textures;

public:
    // Crea un UI_Handler listo para ser utilizado.
    UI_Handler(SDL_Renderer *renderer, Raycaster &raycaster,
               TexturesContainer &tex, std::string font_path, int width,
               int height);

    // Aplica el raycasting sobre el target de renderizado (no lo muestra por
    // pantalla)
    void raycast(DirectedPositionable player_pos, PlayerView view,
                 std::vector<Positionable> objects,
                 std::vector<DirectedPositionable> directed_objects);

    // Limpia el contenido de la ventana.
    void clearScreen();

    // Carga la imagen de fondo del juego.
    void loadBackground();

    // Carga la interfaz informativa de los datos del jugador(vidas, salud, ...)
    void loadPlayerInterface(std::vector<int> player_info);

    // Renderiza el contenido de la ventana.
    void render();

    // Libera los recursos utilzador por el UI_Handler
    ~UI_Handler(){}
};


#endif //WOLFENSTEINCLIENT_UI_HANDLER_H
