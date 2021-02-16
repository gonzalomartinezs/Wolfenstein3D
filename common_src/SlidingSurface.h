#ifndef SLIDINGSURFACE_H
#define SLIDINGSURFACE_H

#include "Timer.h"
#include "Collider.h"

class Map;
class PlayerActions;

class SlidingSurface {
private:
    Timer timer;
    int id;
    int pos_x;
    int pos_y;
    int surface_type;
    int moving_time;
    int opened_time;
    int state;
    float elapsed_fraction;

public:
    // Crea una superficie deslizante lista para ser utilizada.
    // El tiempo es medido en ms.
    SlidingSurface(int id, int x, int y, int surface_type,
                   int opened_time, int moving_time, int initial_state);

    // Actuliza el estado de la puerta
    void update(int new_state);

    void update(Map& map);

    // Retorna el estado actual de la puerta.
    int getState();

    // Retorna un booleano inidicando si la puerta esta abierta.
    bool isOpened() const;

    // Retorna un booleano inidicando si la puerta esta abriendose.
    bool isOpening() const;

    // Retorna un booleano inidicando si la puerta esta cerrada.
    bool isClosed() const;

    // Retorna un booleano inidicando si la puerta esta cerrandose.
    bool isClosing() const;

    // Retorna un valor entre 0 y 1 indicando tiempo_transcurrido/tiempo_limite.
    float getElapsedFraction() const;

    // Retorna la coordenada x de la puerta.
    int getX() const;

    // Retorna la coordenada y de la puerta.
    int getY() const;

    // Retorna el tipo de superficie deslizante.
    int getSurfaceType() const;

    // Retorna el ID de la superficie.
    int getId() const;

    bool collidesWith(const Collider& collider) const;

    void interact(PlayerActions* player);

    // Libera los recursos uilizados por la puerta
    ~SlidingSurface(){}

protected:
    void _updateElapsedFraction();
};


#endif //SLIDINGSURFACE_H
