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
	// Inicializa una key con el archivo de config, debe tener la key radius
	Key(const Configuration& config);
	// Equipa la llave, sólo se puede equipar 1 llave
	void equip();
	// Abre una puerta
	void open(ManualDoor& door);
	// Devuelve true si tiene llave, false si no
	bool has() const;
	// Inicializa KeyItem y lo devuelve en la posición x, y pasadas
	Item* getItem(float x, float y) const;
	// Marca la llave como usada
	void used();
	
	~Key();
};

#endif
