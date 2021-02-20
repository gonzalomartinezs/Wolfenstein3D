#include <iostream>
#include "UI_Handler.h"
#define TTF_TEXTURES 4
#define WEAPONS 5
#define BJ_FACES 8
#define TOTAL_HP 100

enum ttfTextures {Lives, HP, Weapon, Key, Firing, Ammo, Score};

UI_Handler::UI_Handler(SDL_Renderer *renderer, Raycaster &raycaster,
                       TexturesContainer &tex, std::string font_path, int width,
                       int height) : renderer(renderer), raycaster(raycaster), tex(tex){
    int cell_height = (4*height)/18;
    int cell_y_pos = (14*height)/18;

    this->elements.score = {width/32, (16*height)/18, (9*width)/32, cell_height};
    this->elements.lives = {(10*width)/32, (16*height)/18, (4*width)/32, cell_height};
    this->elements.bj_face = {(14*width)/32, cell_y_pos, (4*width)/32, cell_height};
    this->elements.hp = {(18*width)/32, (16*height)/18, (4*width)/32, cell_height};
    this->elements.key = {(22*width)/32, cell_y_pos, (3*width)/32, cell_height};
    this->elements.weapon = {(25*width)/32, cell_y_pos, (6*width)/32, cell_height};
    this->elements.ammo = {(28*width)/32, (9*height)/10, (3*width)/32, cell_height};
    this->elements.weapon_animation = {(10*width)/32, (7*height)/18, (12*width)/32, (7*height)/18};

    SDL_Color color = {240, 250, 252};
    int font_size = width/16;
    for(int i=0; i < TTF_TEXTURES; i++)
        this->font_textures.emplace_back(font_path, font_size, color, renderer, "0");

    for(int i=0; i < WEAPONS; i++){
        this->dynamic.emplace_back(tex.getDynamic(TextureID(Knife_Pl+i)), false);
    }
}

void UI_Handler::raycast(DirectedPositionable &player_pos, PlayerView &view,
                         std::vector<Positionable> &objects,
                         std::vector<DirectedPositionable> &directed_objects,
                         std::vector<int> &doors_states) {
    this->raycaster.draw(player_pos, view, objects, directed_objects, doors_states);
}

void UI_Handler::render() {
    SDL_RenderPresent(this->renderer);
}

void UI_Handler::clearScreen() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
}

void UI_Handler::loadBackground() {
    tex.getStatic(Background)->render(nullptr, nullptr);
}

void UI_Handler::loadPlayerHUD(std::vector<int> &player_info) {
    int bj_face_tex = int(BJ_0) + int((BJ_FACES*(TOTAL_HP-player_info[HP]-1))/TOTAL_HP);

    DynamicTexture& weapon = dynamic[player_info[Weapon]];
    if (player_info[Firing]){
        weapon.getTexture(1)->render(nullptr, &this->elements.weapon_animation);
    } else {
        weapon.getTexture(0)->render(nullptr, &this->elements.weapon_animation);
    }
    tex.getStatic(HUD)->render(nullptr, nullptr);
    tex.getStatic(TextureID(int(Knife_HUD) + player_info[Weapon]))->render(nullptr, &this->elements.weapon);
    tex.getStatic(TextureID(bj_face_tex))->render(nullptr, &this->elements.bj_face);
    tex.getStatic(TextureID(int(HasNotKey) + player_info[Key]))->render(nullptr, &this->elements.key);

    font_textures[0].renderHorizontallyCentered(std::to_string(player_info[Score]), nullptr, &this->elements.score);
    font_textures[1].renderHorizontallyCentered(std::to_string(player_info[Lives]), nullptr, &this->elements.lives);
    font_textures[2].renderHorizontallyCentered(std::to_string(player_info[HP]), nullptr, &this->elements.hp);
    if (player_info[Weapon] != 0)
        font_textures[3].renderHorizontallyCentered(std::to_string(player_info[Ammo]), nullptr, &this->elements.ammo);
    // arreglar hardcodeo
}



