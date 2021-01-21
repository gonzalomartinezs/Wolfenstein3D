#include <iostream>
#include "UI_Handler.h"
#define TTF_TEXTURES 4
#define BJ_FACES 8
#define TOTAL_HP 100
enum ttfTextures {Lives, HP, Key, Weapon, Score, Ammo};

UI_Handler::UI_Handler(SDL_Renderer *renderer, Raycaster &raycaster,
                       TexturesContainer &tex, std::string font_path, int width,
                       int height) : renderer(renderer), raycaster(raycaster), tex(tex){
    int cell_height = (4*height)/18;
    int cell_y_pos = (16*height)/18;
    this->elements.score = {width/32, cell_y_pos, (9*width)/32, cell_height};
    this->elements.lives = {(10*width)/32, cell_y_pos, (4*width)/32, cell_height};
    this->elements.bj_face = {(14*width)/32, cell_y_pos, (4*width)/32, cell_height};
    this->elements.hp = {(18*width)/32, cell_y_pos, (4*width)/32, cell_height};
    this->elements.key = {(22*width)/32, cell_y_pos, (3*width)/32, cell_height};
    this->elements.weapon = {(25*width)/32, cell_y_pos, (6*width)/32, cell_height};
    this->elements.ammo = {(28*width)/32, (9*height)/10, (3*width)/32, cell_height};
    SDL_Color color = {240, 250, 252};
    int font_size = width/16;
    for(int i=0; i < TTF_TEXTURES; i++)
        this->font_textures.emplace_back(font_path, font_size, color, renderer, "0");
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

void UI_Handler::loadPlayerInterface(std::vector<int> player_info) {
    int bj_face_tex = int(BJ_0) + int((BJ_FACES*(TOTAL_HP-player_info[HP]))/TOTAL_HP);
    tex.get(MainInterface)->render(nullptr, nullptr);
    tex.get(TextureID(int(KnifeInterface) + player_info[Weapon]))->render(nullptr, &this->elements.weapon);
    tex.get(TextureID(bj_face_tex))->render(nullptr, &this->elements.bj_face);
    tex.get(TextureID(int(HasNotKey)+player_info[Key]))->render(nullptr, &this->elements.key);
    font_textures[Score].renderHorizontallyCentered(std::to_string(player_info[Score]), nullptr,
                                                 &this->elements.score);
    font_textures[Lives].renderHorizontallyCentered(std::to_string(player_info[Lives]), nullptr,
                                                &this->elements.lives);
    font_textures[HP].renderHorizontallyCentered(std::to_string(player_info[HP]), nullptr,
                                                 &this->elements.hp);
    font_textures[Ammo].renderHorizontallyCentered(std::to_string(player_info[Ammo]), nullptr,
                                                 &this->elements.ammo);
}



