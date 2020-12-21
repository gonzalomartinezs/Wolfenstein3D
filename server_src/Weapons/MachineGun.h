#ifndef WOLFENSTEIN3D_MACHINEGUN_H
#define WOLFENSTEIN3D_MACHINEGUN_H

#include "Weapon.h"

class MachineGun : public Weapon {
public:
	MachineGun();
	void fireTheGun(std::vector<Player>& players, int shootingPlayerNumber,
					const Map& map) override;
    void startShooting() override;
	~MachineGun();
};

#endif  // WOLFENSTEIN_MACHINEGUN_H
