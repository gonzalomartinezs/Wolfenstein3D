#ifndef KEY_H
#define KEY_H

#include "../client_src/textures/TextureID.h"
#include "../common_src/Configuration.h"
#include "../common_src/ManualDoor.h"

class Item;

class Key {
private:
	TextureID item_texture;
	const float item_radius;
	bool available;
public:
	Key(const Configuration& config);
	void equip();
	void open(ManualDoor& door);
	bool has() const;
	Item* getItem(float x, float y) const;
	void used();
	~Key();
};

#endif
