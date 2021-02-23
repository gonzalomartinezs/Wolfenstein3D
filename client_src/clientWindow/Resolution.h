#ifndef WOLFENSTEINCLIENT_RESOLUTION_H
#define WOLFENSTEINCLIENT_RESOLUTION_H

#include <string>

// Clase resolucion, representa una resolucion de pantalla.
class Resolution {
public:
    Resolution (int x = 480, int y = 320);
    int getX() const;
    int getY() const;
    // Retorna un string de la forma (X,Y). Permite imprimirlo con mas facilidad.
    std::string toString() const;
private:
    int x;
    int y;
};


#endif //WOLFENSTEINCLIENT_RESOLUTION_H
