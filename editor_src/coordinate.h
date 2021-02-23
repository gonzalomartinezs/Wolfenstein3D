#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>

/* Clase Coordenada */
class Coordinate {
  public:
    Coordinate(unsigned x = 0, unsigned y = 0 );
    //Devuelve el componente entero correspondiente a X
    unsigned getX()const;
    //Devuelve el componente entero correspondiente a Y
    unsigned getY()const;

    //Retorna un string de la forma "x,y".
    std::string toString()const;

    bool operator==(const Coordinate& r)const;
    Coordinate& operator=(const Coordinate&);

  private:
    unsigned x;
    unsigned y;
};

#endif // COORDINATE_H
