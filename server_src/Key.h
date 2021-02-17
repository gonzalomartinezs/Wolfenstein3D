#ifndef KEY_H
#define KEY_H

#include "../client_src/textures/TextureID.h"
#include "../common_src/Configuration.h"

class Item;

class Key {
private:
	TextureID item_texture;
	const float item_radius;
	bool available;
public:
	Key(const Configuration& config);
	void equip();
	bool has() const;
	Item* getItem(float x, float y) const;
	void used();
	~Key();
};

#endif
