#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include "../client_src/textures/TextureID.h"

class Positionable {
protected:
    float x;
    float y;
    TextureID texture;
public:
    // Crea un posicionable listo para ser utilizado.
    Positionable(float x, float y, TextureID tex): x(x), y(y), texture(tex){}

    // Establecen una nueva coordenada x e y del posicionable.
    void setX(float new_x);
    void setY(float new_y);

    //Desplazan las coordenadas x e y actuales de acuerdo al parametro recibido.
    void moveX(float x_movement);
    void moveY(float y_movement);

    // Retornan los valores de las coordenadas x e y respectivamente.
    float getX() const;
    float getY() const;

    // Retorna el ID de la textura del posicionble.
    TextureID getTexture();

    // Libera los recursos utilizados por el posicionable.
    ~Positionable(){}

};


#endif //POSITIONABLE_H
