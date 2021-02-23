#ifndef UI_HANDLER_H
#define UI_HANDLER_H

#include <SDL2/SDL.h>
#include "Raycaster.h"
#include "textures/TexturesContainer.h"
#include "textures/FontTexture.h"
#include "textures/DynamicTexture.h"
#include "LeaderboardRenderer.h"

struct HUDElements{
    SDL_Rect score;
    SDL_Rect lives;
    SDL_Rect hp;
    SDL_Rect key;
    SDL_Rect weapon;
    SDL_Rect ammo;
    SDL_Rect bj_face;
    SDL_Rect weapon_animation;
    SDL_Rect death_message;
};

class UI_Handler {
private:
    SDL_Renderer* renderer;
    Raycaster& raycaster;
    TexturesContainer& tex;
    HUDElements elements;
    LeaderboardRenderer leaderboard;
    std::vector<FontTexture> font_textures;
    std::vector<DynamicTexture> dynamic;

public:
    // Crea un UI_Handler listo para ser utilizado.
    UI_Handler(SDL_Renderer *renderer, Raycaster &raycaster,
               TexturesContainer &tex, const std::string& font_path, int width,
               int height);

    // Aplica el raycasting sobre el target de renderizado (no lo muestra por
    // pantalla)
    void raycast(DirectedPositionable &player_pos, PlayerView &view,
                 std::vector<Positionable> &objects,
                 std::vector<DirectedPositionable> &directed_objects,
                 std::vector<int> &doors_states, bool not_playing);

    // Limpia el contenido de la ventana.
    void clearScreen();

    // Carga la imagen de fondo del juego.
    void loadBackground();

    // Carga la interfaz informativa de los datos del jugador(vidas, salud, ...)
    void loadPlayerHUD(std::vector<int> &player_info);

    // Muestra el leaderboard del juego por pantalla.
    void loadLeaderboard(std::vector<std::string> &names,
                         std::vector<int> &values);

    // Realiza la animacion de la vista del jugador.
    void loadDeathTilt();

    // Muestra por pantalla un mensaje indicando que el jugador ha perdido
    // todas sus vidas.
    void loadGameOverMessage();

    // Renderiza el contenido de la ventana.
    void render();

    // Libera los recursos utilzador por el UI_Handler
    ~UI_Handler(){}

};


#endif //WOLFENSTEINCLIENT_UI_HANDLER_H
