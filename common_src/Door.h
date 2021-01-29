#ifndef DOOR_H
#define DOOR_H
#include "Timer.h"

class Door {
private:
    Timer timer;
    int state;
    int pos_x;
    int pos_y;
    int door_moving_time;
    int door_opened_limit;
    float fraction_remaining;

public:
    // Crea una puerta lista para ser utilizada. El tiempo es medido en ms.
    Door(int x, int y, int moving_time, int opened_limit,
         int initial_state);

    // Actuliza el estado de la puerta
    void update(int new_state);

    // Retorna el estado actual de la puerta.
    int getState();

    // Retorna un booleano inidicando si la puerta esta abierta.
    bool isOpened();

    // Retorna un booleano inidicando si la puerta esta abriendose.
    bool isOpening();

    // Retorna un booleano inidicando si la puerta esta cerrada.
    bool isClosed();

    // Retorna un booleano inidicando si la puerta esta cerrandose.
    bool isClosing();

    // Retorna un valor entre 0 y 1 indicando tiempo_transcurrido/tiempo_limite.
    float getFractionRemaining();

    // Retorna la coordenada x de la puerta.
    int getX();

    // Retorna la coordenada y de la puerta.
    int getY();

    // Libera los recursos uilizados por la puerta
    ~Door(){};

private:
    void _updateFractionRemaining();
};


#endif //DOOR_H
