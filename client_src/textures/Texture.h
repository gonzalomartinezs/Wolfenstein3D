#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <string>

class Texture {
private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;

public:
    // Crea una textura en base al path recibido.
    Texture(std::string path, SDL_Renderer* renderer,
                                                SDL_Surface* surface=nullptr);

    // Toma el fragmento source de la textura y lo adapta a la forma de dest.
    void render(SDL_Rect* source, SDL_Rect* dest);

    // Modula el color de la textura de acuerdo a mod.
    void changeColorModulation(Uint8 mod);

    // Libera los recursos utilizados por la terxtura.
    ~Texture();
};


#endif //TEXTURE_H
