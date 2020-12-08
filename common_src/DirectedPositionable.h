#ifndef DIRECTED_POSITIONABLE_H
#define DIRECTED_POSITIONABLE_H

#include "Positionable.h"

class DirectedPositionable: public Positionable{
private:
    float dir_x;
    float dir_y;

public:
    // Crea un posicionable dirigdo listo para ser utilizado.
    explicit DirectedPositionable(float pos_x, float pos_y,
                                  float dir_x, float dir_y);

    DirectedPositionable operator=(const DirectedPositionable& other);

    // Establecen una nueva direccion para el posicionable.
    void setDirX(float new_dir);
    void setDirY(float new_dir);

    // Retornan la dirección x e y del poscionable.
    float getDirX() const;
    float getDirY() const;

    // Libera los recursos utilziados por el posicionable dirigido.
    ~DirectedPositionable(){}

};


#endif //DIRECTED_POSITIONABLE_H
