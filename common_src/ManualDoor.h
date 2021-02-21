#ifndef MANUALDOOR_H
#define MANUALDOOR_H

#include "Timer.h"
#include "Map.h"
#include "Positionable.h"
#include "Collider.h"
#include "RectCollider.h"

class ManualDoor : public Positionable {
protected:
	const int dir_x, dir_y;
	uint8_t state;
	const int surface_type;
	const float moving_time;
	float elapsed_fraction;
	bool locked;
	RectCollider collider;
	Timer timer;

public:
	ManualDoor(int _x, int _y, int _dir_x, int _dir_y, int _surface_type,
				float _moving_time, bool is_locked);

	// Actualiza el estado de la puerta del lado del servidor
	virtual void update(Map& map, const std::vector<Collider>& players);

	// Actualiza el estado de la puerta del lado del cliente
	virtual void update(int new_state);

	// Obtiene el estado actual
	uint8_t getState() const;

	bool isClosed() const;

	bool isClosing() const;

	bool isOpened() const;

	bool isOpening() const;

	float getElapsedFraction() const;

	int getSurfaceType() const;

	// Abre o cierra la puerta dependiendo del tipo de puerta y si necesita
	// llave o no (has_key)
	virtual void interact(bool has_key);

	// Devuelve true si colisiona con other_collider, false en caso contrario
	bool collidesWith(const Collider& other_collider);

	virtual ~ManualDoor();

protected:
	// Devuelve true en caso de que un jugador obstruya la pared, false
	// en caso contrario
	bool isPlayerBlockingDoor(const std::vector<Collider>& players);
	// Actualiza el valor de elapsed_fraction
	virtual void _updateElapsedFraction();
};

#endif
