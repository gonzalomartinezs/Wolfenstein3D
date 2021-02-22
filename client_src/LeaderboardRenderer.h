#ifndef LEADERBOARDRENDERER_H
#define LEADERBOARDRENDERER_H

#include "textures/TexturesContainer.h"
#include "textures/FontTexture.h"

class LeaderboardRenderer {
private:
    TexturesContainer& tex;
    SDL_Renderer* renderer;
    std::vector<FontTexture> titles;
    std::vector<FontTexture> names;
    std::vector<FontTexture> values;
    int height;
    int width;

public:
    // Crea un renderizador de leaderboard listo para ser utilizado.
    LeaderboardRenderer(SDL_Renderer *renderer,
                        TexturesContainer &tex,
                        const std::string &font_path,
                        int height, int width);

    // Renderiza el leaderboard.
    void render(std::vector<std::string> &names, std::vector<int> &values);

    // Libera los recursos utilizados por el renderer.
    ~LeaderboardRenderer();

private:
    void _render();
};


#endif //LEADERBOARDRENDERER_H
