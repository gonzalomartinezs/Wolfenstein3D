#ifndef PLAYERATTRIBUTES_H
#define PLAYERATTRIBUTES_H

#include <cstdint>

class PlayerAttributes {
private:
	uint8_t health, lives;
    int score;
    bool hasKey;
public:
	PlayerAttributes();
	void addHealth(int _health);
	bool isDead() const;
	~PlayerAttributes();
};

#endif
