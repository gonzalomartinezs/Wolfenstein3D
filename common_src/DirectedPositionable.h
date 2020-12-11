#ifndef DIRECTED_POSITIONABLE_H
#define DIRECTED_POSITIONABLE_H

#include "Positionable.h"
#include "../client_src/textures/TextureID.h"

class DirectedPositionable: public Positionable{
protected:
    float dir_x;
    float dir_y;

public:
    // Crea un posicionable dirigido listo para ser utilizado.
    explicit DirectedPositionable(float pos_x, float pos_y,
                                  float dir_x, float dir_y,
                                  TextureID texture);

    DirectedPositionable& operator=(const DirectedPositionable& other);

    // Establecen una nueva direccion para el posicionable. Deberian ser un unico metodo??
    void setDirX(float new_dir);
    void setDirY(float new_dir);

    // Retornan la dirección x e y del poscionable.
    float getDirX() const;
    float getDirY() const;

    // Modifica la textura actual del posicionable.
    void setTexture(TextureID texture);

    // Libera los recursos utilzados por el posicionable dirigido.
    ~DirectedPositionable(){}

};


#endif //DIRECTED_POSITIONABLE_H
