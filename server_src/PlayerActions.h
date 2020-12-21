#ifndef PLAYERATTRIBUTES_H
#define PLAYERATTRIBUTES_H

#include <cstdint>

class HealthRecover;
class Treasure;

class PlayerAttributes {
private:
	uint8_t health, lives;
    int score;
    bool hasKey;
public:
	PlayerAttributes();
	void use(HealthRecover* recover);
	void use(Treasure* treasure);
	bool isDead() const;
	~PlayerAttributes();
};

#endif
