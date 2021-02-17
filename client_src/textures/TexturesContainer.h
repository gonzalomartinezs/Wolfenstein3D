#ifndef TEXTURESCONTAINER_H
#define TEXTURESCONTAINER_H
#include <SDL2/SDL_render.h>
#include <unordered_map>
#include "DynamicTexture.h"
#include "TextureID.h"
#include "Texture.h"

class TexturesContainer {
private:
    std::unordered_map<TextureID, Texture*> static_textures;
    std::unordered_map<TextureID, DynamicTexture*> dynamic_textures;
    SDL_Renderer* renderer;
    SDL_Surface* window_surface;

public:
    // Crea un contenedor de texturas con todas las texturas del juego cargadas
    TexturesContainer(SDL_Renderer *renderer, SDL_Surface *window_surface);

    // Retorna un puntero a la textura estatica solicitada.
    Texture* getStatic(TextureID id);

    // Retorna un puntero a la textura dinamica solicitada.
    DynamicTexture* getDynamic(TextureID id);

    // Libera los recursos utilizados por el contenedor.
    ~TexturesContainer();

private:
    void _loadStaticTextures();
    void _loadDynamicTextures();
};


#endif //TEXTURESCONTAINER_H
