#include <iostream>
#include "UI_Handler.h"

UI_Handler::UI_Handler(SDL_Renderer *renderer, Raycaster &raycaster,
                       TexturesContainer &tex, int width, int height)
        : renderer(renderer), raycaster(raycaster), tex(tex){
    this->window = {0, 0, width, height};
}

void UI_Handler::raycast(DirectedPositionable player_pos, PlayerView view,
                         std::vector<Positionable> objects,
                         std::vector<DirectedPositionable> directed_objects) {
    this->raycaster.draw(player_pos, view, objects, directed_objects);
}

void UI_Handler::render() {
    SDL_RenderPresent(this->renderer);
}

void UI_Handler::clearScreen() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
}

void UI_Handler::loadBackground() {
    tex.get(Background)->render(nullptr, nullptr);
}

void UI_Handler::loadPlayerInterface() {
    tex.get(MainInterface)->render(nullptr, nullptr);
}



