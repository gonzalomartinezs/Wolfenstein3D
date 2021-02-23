#include "DynamicTexture.h"
#define MOVING 1
#define STILL 0
DynamicTexture::DynamicTexture(TextureSet *textures, bool single_event) :
                               textures(textures), period(textures->getPeriod()),
                               state(STILL), single_event(single_event){
}

void DynamicTexture::updateSet(TextureSet *texture) {
    this->textures = texture;
}

Texture *DynamicTexture::getTexture(int new_state) {
    float fraction = timer.getTime()/(float)period;

    if (state == MOVING && fraction < 1){
        int index = int(fraction * textures->size()) % textures->size();
        return textures->get(index);
    } else if (new_state == MOVING){
        timer.start();
    }
    state = new_state;
    return textures->get(0);
}

DynamicTexture::~DynamicTexture() {}






