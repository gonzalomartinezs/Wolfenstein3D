#ifndef FONT_H
#define FONT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class FontTexture {
private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color color;
    std::string latest_value;

public:
    // Crea una textura de tipografia lista para ser utiliazada.
    FontTexture(std::string font_path, int font_size, SDL_Color font_color,
                SDL_Renderer *renderer, std::string value);

    // Constructor por movimiento.
    FontTexture(FontTexture&& other) noexcept ;

    // Elimino el constructor por copia y los operadores asignacion.
    FontTexture(FontTexture& other) = delete;
    FontTexture& operator=(FontTexture& other) = delete;
    FontTexture& operator=(FontTexture&& other) = delete;

    // Renderiza el texto centrado horizontalemente en el rectangulo dest.
    void renderHorizontallyCentered(std::string new_value, SDL_Rect* source,
                                    SDL_Rect* dest);

    // Libera los recursos utilizados por la fuente.
    ~FontTexture();
};


#endif //FONT_H
