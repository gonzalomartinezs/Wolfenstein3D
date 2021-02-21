#ifndef SLIDINGSURFACE_H
#define SLIDINGSURFACE_H

#include "ManualDoor.h"

class Map;

class SlidingSurface : public ManualDoor {
private:
    int opened_time;

public:
    // Crea una superficie deslizante lista para ser utilizada.
    // El tiempo es medido en ms.
    SlidingSurface(int _x, int _y, int _dir_x, int _dir_y,
                    int _surface_type, float _moving_time, bool is_locked,
                    int opened_time);

    void update(Map& map, const std::vector<Collider>& players) override;

    void interact(bool has_key) override;

    // Libera los recursos uilizados por la puerta
    ~SlidingSurface();

private:
    void _updateElapsedFraction() override;
};


#endif //SLIDINGSURFACE_H
