#ifndef POSITIONABLE_H
#define POSITIONABLE_H


class Positionable {
private:
    float x;
    float y;
public:
    // Crea un posicionable listo para ser utilizado.
    Positionable(float x, float y): x(x), y(y){}

    // Establecen una nueva coordenada x e y del posicionable.
    void setX(float new_x);
    void setY(float new_y);

    //Desplazan las coordenadas x e y actuales de acuerdo al parametro recibido.
    void moveX(float x_movement);
    void moveY(float y_movement);

    // Retornan los valores de las coordenadas x e y respectivamente.
    float getX() const;
    float getY() const;

    // Libera los recursos utilizados por el posicionable.
    ~Positionable(){}

};


#endif //POSITIONABLE_H
