#include "DynamicTexture.h"
#define MOVING 1
#define STILL 0

DynamicTexture::DynamicTexture(std::vector<std::string> paths,
                               SDL_Renderer *renderer, SDL_Surface *surface,
                               int period): period(period), state(STILL){
    for (auto& path: paths){
            textures.emplace_back(path, renderer, surface);
    }
    timer.start();
}

void DynamicTexture::updatePeriod(int new_period) {
    this->period = new_period;
    timer.start();
}

Texture &DynamicTexture::getTexture(int new_state) {
    if(state == new_state && state == MOVING){
        state = new_state;
        float fraction = timer.getTime()/(float)period;
        int index = int(fraction * textures.size()) % textures.size();
        return textures[index];
    } else if (new_state == MOVING){
        timer.start();
    }
    state = new_state;
    return textures[0];
}




